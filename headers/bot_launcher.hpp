// Copyright [2023] <Volodymyr Dorozhovets>"

#ifndef BOT_LAUNCHER_HPP
#define BOT_LAUNCHER_HPP

#include <future>

#include <tgbot/tgbot.h>

#include "program_completion_status.hpp"
#include "manager/database.hpp"
#include "thread_pool.hpp"
#include "logger.hpp"
#include "telegram_bot_tagging.hpp"


namespace N_TelegramBotTagging
{
class BotLauncher
{
public:
	inline BotLauncher();

	ProgramCompletionStatus Start();
private:
	TelegramBotTagging m_telegram_bot_tagging;

	ThreadPool m_thread_pool;

	N_Database::Manager m_database_manager;

	Logger m_logger;

	std::future<ProgramCompletionStatus> m_future_of_threads_exception_handler;

	std::thread m_thread_of_threads_exception_handler;
private:
	void LaunchThreadsExceptionHandler();

	ProgramCompletionStatus GetThreadsExceptionHandlerResult();

	void LaunchLogger();

	void LaunchTelegramBotTagging();
};

inline BotLauncher::BotLauncher()
	: m_telegram_bot_tagging(&m_logger, &m_database_manager, &m_thread_pool),
	  m_logger(m_thread_pool)
{
}
}  // namespace N_TelegramBotTagging

#endif  // BOT_LAUNCHER_HPP
