// Copyright [2023] <Volodymyr Dorozhovets>"

#if defined(_WIN32)
#include "framework.hpp"
#endif

#include "bot_launcher.hpp"
#include "threads_exception_handler.hpp"


namespace N_TelegramBotTagging
{
ProgramCompletionStatus BotLauncher::Start()
{
	this->LaunchThreadsExceptionHandler();

	this->LaunchLogger();

	this->LaunchTelegramBotTagging();

	ProgramCompletionStatus result{this->GetThreadsExceptionHandlerResult()};

	return result;
}

void BotLauncher::LaunchThreadsExceptionHandler()
{
	std::promise<ProgramCompletionStatus> promise;
	this->m_future_of_threads_exception_handler = promise.get_future();
	this->m_thread_of_threads_exception_handler
		= std::thread(ThreadsExceptionHandler(&this->m_thread_pool, &this->m_logger), std::move(promise));
}

ProgramCompletionStatus BotLauncher::GetThreadsExceptionHandlerResult()
{
	ProgramCompletionStatus result{this->m_future_of_threads_exception_handler.get()};
	this->m_thread_of_threads_exception_handler.join();

	return result;
}

void BotLauncher::LaunchLogger()
{
	m_thread_pool.PushTask(&this->m_logger);
}

void BotLauncher::LaunchTelegramBotTagging()
{
	m_thread_pool.PushTask(&this->m_telegram_bot_tagging);
}
}  // namespace N_TelegramBotTagging
