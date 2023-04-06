// Copyright [2023] <Volodymyr Dorozhovets>"

#if defined(_WIN32)
#include "framework.hpp"
#endif

#include "threads_exception_handler.hpp"
#include "exception/thread_timeout.hpp"
#include "exception/error_writing_data_to_error_log_file.hpp"
#include "error/flags.hpp"
#include "error/messages.hpp"


namespace N_TelegramBotTagging
{
void ThreadsExceptionHandler::operator()(std::promise<ProgramCompletionStatus> &&promise)
{
	const bool &threading_enabled = m_thread_pool->IsThreadingEnabled();
	while(threading_enabled)
	{
		HandleThreadsResults(ThreadsExceptionHandler::S_DEFAULT_WAIT_DURATION);
	}

	HandleThreadsResults(ThreadsExceptionHandler::S_DEFAULT_EXCEPTION_THROWN_WAIT_DURATION);

	this->FlushDataOfLogger();
	this->Handle();
	this->PrintErrorMessage();

	promise.set_value(this->m_program_status);
}

void ThreadsExceptionHandler::HandleThreadResult(std::future<void> &&result)
{
	try
	{
		try
		{
			result.get();
		}
		catch (...)
		{
			if (this->m_program_status != ProgramCompletionStatus::critical)
			{
				this->m_program_status = ProgramCompletionStatus::error;
			}

			this->TrySetExceptionOfWritingDataToErrorLogFile(std::current_exception());
			this->m_thread_pool->Pause();
		}
	}
	catch(...)
	{
		this->TrySetCriticalProgramStatus(std::current_exception());
	}
}

void ThreadsExceptionHandler::TrySetCriticalProgramStatus(const std::exception_ptr &exception)
{
	try
	{
		std::rethrow_exception(exception);
	}
	catch(const N_Exception::ThreadTimeout &)
	{
		(void)this->m_exceptions.emplace_back(exception);
		this->m_program_status = ProgramCompletionStatus::critical;
		this->m_error_flags |= static_cast<int>(N_Error::Flags::critical);
	}
	catch(...)
	{
		(void)this->m_exceptions.emplace_back(exception);
	}
}

void ThreadsExceptionHandler::TrySetExceptionOfWritingDataToErrorLogFile(const std::exception_ptr &exception)
{
	try
	{
		std::rethrow_exception(exception);
	}
	catch(const N_Exception::ErrorWritingDataToErrorLogFile &)
	{
		(void)this->m_exceptions.emplace_back(exception);
		m_is_exception_writing_data_to_error_log_file = true;
	}
	catch(...)
	{
		(void)this->m_exceptions.emplace_back(exception);
	}
}

void ThreadsExceptionHandler::FlushDataOfLogger()
{
	this->TryFlushLoggerMethodData([&]()
								   {
									   this->m_logger->LogProgramStatus();
								   });

	this->TryFlushLoggerMethodData([&]()
								   {
									   this->m_logger->LogUserRequests();
								   });

	this->TryFlushLoggerMethodData([&]()
								   {
									   this->m_logger->LogErrors();
								   });
}

void ThreadsExceptionHandler::TryFlushLoggerMethodData(const std::function<void()> &method)
{
try
	{
		method();
	}
	catch(...)
	{
		this->TrySetExceptionOfWritingDataToErrorLogFile(std::current_exception());
	}
}

void ThreadsExceptionHandler::Handle()
{
	for(std::size_t i{0UL}; i < this->m_exceptions.size(); ++i)
	{
		if(m_is_exception_writing_data_to_error_log_file)
		{
			this->HandleWithConsoleOutput(m_exceptions[i]);
		}
		else
		{
			this->HandleWithLogging(m_exceptions[i]);
		}
	}
}

void ThreadsExceptionHandler::HandleWithConsoleOutput(const std::exception_ptr &exception)
{
    try
	{
		std::rethrow_exception(exception);
	}
	catch(std::exception &caught_exception)
	{
		this->m_error_flags |= static_cast<int>(N_Error::Flags::error);
		std::cout << typeid(caught_exception).name() << ": " << caught_exception.what() << "\n" << std::endl;
	}
	catch(...)
	{
		this->m_error_flags |= static_cast<int>(N_Error::Flags::unspecified);
		std::cout << N_Error::N_Messages::G_UNSPECIFIED << "\n" << std::endl;
	}
}

void ThreadsExceptionHandler::HandleWithLogging(const std::exception_ptr &exception)
{
	try
	{
		try
		{
			std::rethrow_exception(exception);
		}
		catch(std::exception &caught_exception)
		{
			this->m_error_flags |= static_cast<int>(N_Error::Flags::error);

			std::string message;
			message += typeid(caught_exception).name(); message += ": ";
			message += caught_exception.what(); message += "\n\n";
			this->m_logger->LogErrors(message);
		}
		catch(...)
		{
			this->m_error_flags |= static_cast<int>(N_Error::Flags::unspecified);

			std::string message;
			message += N_Error::N_Messages::G_UNSPECIFIED; message += "\n\n";

			this->m_logger->LogErrors(message);
		}
	}
	catch(const N_Exception::ErrorWritingDataToErrorLogFile &)
	{
		this->m_is_exception_writing_data_to_error_log_file = true;
		(void)this->m_exceptions.emplace_back(std::current_exception());
	}
}

inline void ThreadsExceptionHandler::PrintErrorMessage() const
{
	this->TryPrintMinorMessage		();
	this->TryPrintErrorMessage		();
	this->TryPrintCriticalMessage   ();
	this->TryPrintUnspecifiedMessage();
}

inline void ThreadsExceptionHandler::TryPrintMinorMessage() const
{
	bool result = this->m_error_flags & static_cast<int>(N_Error::Flags::minor);
	if(result)
	{
		std::cout << N_Error::N_Messages::G_MINOR << " " << N_Error::N_Messages::G_LOG_FILE_HINT << std::endl;
	}
}

inline void ThreadsExceptionHandler::TryPrintErrorMessage() const
{
	bool result = this->m_error_flags & static_cast<int>(N_Error::Flags::error);
	if(result)
	{
		std::cout << N_Error::N_Messages::G_ERROR << " " << N_Error::N_Messages::G_LOG_FILE_HINT << std::endl;
	}
}

inline void ThreadsExceptionHandler::TryPrintCriticalMessage() const
{
	bool result = this->m_error_flags & static_cast<int>(N_Error::Flags::critical);
	if(result)
	{
		std::cout << N_Error::N_Messages::G_CRITICAL << " " << N_Error::N_Messages::G_LOG_FILE_HINT << std::endl;
	}
}

inline void ThreadsExceptionHandler::TryPrintUnspecifiedMessage() const
{
	bool result = this->m_error_flags & static_cast<int>(N_Error::Flags::unspecified);
	if(result)
	{
		std::cout << N_Error::N_Messages::G_UNSPECIFIED << " " << N_Error::N_Messages::G_LOG_FILE_HINT << std::endl;
	}
}
}  // namespace N_TelegramBotTagging
