// Copyright [2023] <Volodymyr Dorozhovets>"

#ifndef THREADS_EXCEPTION_HANDLER_HPP
#define THREADS_EXCEPTION_HANDLER_HPP

#include "thread_pool.hpp"
#include "logger.hpp"
#include "program_completion_status.hpp"


namespace N_TelegramBotTagging
{
class ThreadsExceptionHandler
{
public:
	explicit inline ThreadsExceptionHandler(ThreadPool *thread_pool,
											Logger     *logger);

	void operator()(std::promise<ProgramCompletionStatus> &&promise);
private:
	template<typename Rep, typename Period>
	using T_Duration = std::chrono::duration<Rep, Period>;

	inline static constexpr std::chrono::milliseconds S_DEFAULT_WAIT_DURATION			      {100 };
	inline static constexpr std::chrono::milliseconds S_DEFAULT_EXCEPTION_THROWN_WAIT_DURATION{1000};
private:
	ThreadPool *m_thread_pool;

	Logger *m_logger;

	std::vector<std::exception_ptr> m_exceptions;

	bool m_is_exception_writing_data_to_error_log_file;

	int m_error_flags;

	ProgramCompletionStatus m_program_status;
private:
	template<typename Rep, typename Period>
	void HandleThreadsResults(const T_Duration<Rep, Period> &duration);

	void HandleThreadResult(std::future<void> &&result);

	void TrySetCriticalProgramStatus(const std::exception_ptr &exception);

	void TrySetExceptionOfWritingDataToErrorLogFile(const std::exception_ptr &exception);

	void FlushDataOfLogger();
	void TryFlushLoggerMethodData(const std::function<void()> &method);

	void Handle();

	void HandleWithConsoleOutput(const std::exception_ptr &exception);

	void HandleWithLogging(const std::exception_ptr &exception);

	inline void PrintErrorMessage() const;

	inline void TryPrintMinorMessage	  () const;
	inline void TryPrintErrorMessage      () const;
	inline void TryPrintCriticalMessage   () const;
	inline void TryPrintUnspecifiedMessage() const;
};

inline ThreadsExceptionHandler::ThreadsExceptionHandler(ThreadPool *thread_pool,
														Logger     *logger)
	: m_thread_pool(thread_pool),
	  m_logger(logger),
	  m_is_exception_writing_data_to_error_log_file(false),
	  m_error_flags(0),
	  m_program_status(ProgramCompletionStatus::success)
{
}

template<typename Rep, typename Period>
void ThreadsExceptionHandler::HandleThreadsResults(const T_Duration<Rep, Period> &duration)
{
	auto &threads_results = m_thread_pool->GetThreadsResults();

	auto thread_result = threads_results.begin();
	while(thread_result != threads_results.end())
	{
		if (thread_result->wait_for(duration) == std::future_status::ready)
		{
			this->HandleThreadResult(std::move(*thread_result));
			thread_result = threads_results.erase(thread_result);
		}
		else
		{
			++thread_result;
		}
	}
}
}  // namespace N_TelegramBotTagging

#endif  // THREADS_EXCEPTION_HANDLER_HPP
