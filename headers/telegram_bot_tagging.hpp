// Copyright [2023] <Volodymyr Dorozhovets>"

#ifndef TELEGRAM_BOT_TAGGING_HPP
#define TELEGRAM_BOT_TAGGING_HPP

#include "database.hpp"
#include "logger.hpp"
#include "thread_pool.hpp"
#include "command/handler/start.hpp"
#include "command/handler/help.hpp"
#include "command/handler/sign.hpp"
#include "command/handler/tag.hpp"
#include "command/handler/settings.hpp"
#include "command/callback/settings.hpp"


namespace N_TelegramBotTagging
{
class TelegramBotTagging
{
public:
	inline explicit TelegramBotTagging(Logger 			   *logger,
									   N_Database::Manager *database_manager,
									   ThreadPool          *thread_pool);

	void operator()();
private:
	using T_Requests = std::vector<std::shared_ptr<TgBot::Update>>;
	using T_GroupIds = std::vector<int64_t>;
private:
	std::unique_ptr<TgBot::Bot> 	   m_bot;
	std::unique_ptr<TgBot::TgLongPoll> m_long_poll;

	Logger 				*m_logger;
	N_Database::Manager *m_database_manager;
	ThreadPool 			*m_thread_pool;
private:
	std::unique_ptr<N_Command::N_Handler::Start>     m_start_command_handler;
	std::unique_ptr<N_Command::N_Handler::Help>      m_help_command_handler;
	std::unique_ptr<N_Command::N_Handler::Settings>  m_settings_command_handler;
	std::unique_ptr<N_Command::N_Callback::Settings> m_settings_command_callback;
	std::unique_ptr<N_Command::N_Handler::Sign>      m_sign_command_handler;
	std::unique_ptr<N_Command::N_Handler::Tag> 	     m_tag_command_handler;

	inline void CreateBot(std::string_view api_token);
	inline void CreateLongPolling();
	void CreateCommandHandlers();

	T_Requests CancelAllRequests();

	std::string GetMessageOfNumberOfCanceledRequests(const T_Requests &requests);

	inline void ClearPendingRequestsFromDatabase();

	inline static void DisplayMessageOfNumberOfCanceledRequestsOnConsole(std::string_view message) noexcept;
	inline 		  void SaveMessageOfNumberOfCanceledRequestsInLog	    (std::string_view message);

	std::size_t GetTotalPendingRequestsFromDatabase();

	T_GroupIds GetGroupIdsWithPendingRequests(const T_Requests &requests);

	static T_GroupIds GetGroupIdsFromRequests(const T_Requests &requests);

	T_GroupIds GetGroupIdsFromDatabase();

	static T_GroupIds MergeGroupIds(T_GroupIds &&first_group_ids,
								    T_GroupIds &&second_group_ids);

	inline static void RemoveDuplicateGroupIds(T_GroupIds *group_ids);

	void InformGroupsOfServerIssues(const T_GroupIds &group_ids);

	void InstallCommandHandlers		   ();
	void InstallStartCommandHandler	   ();
	void InstallHelpCommandHandler	   ();
	void InstallSettingsCommandHandler ();
	void InstallSettingsCommandCallback();
	void InstallSignCommandHandler	   ();
	void InstallTagCommandHandler	   ();

	void LaunchLongPolling();
};

inline TelegramBotTagging::TelegramBotTagging(Logger 		      *logger,
											  N_Database::Manager *database_manager,
											  ThreadPool 	      *thread_pool)
	: m_logger		    (logger		     ),
	  m_database_manager(database_manager),
	  m_thread_pool	    (thread_pool	 )
{
}

inline void TelegramBotTagging::CreateBot(const std::string_view api_token)
{
	this->m_bot = std::make_unique<TgBot::Bot>(api_token.data());
}

inline void TelegramBotTagging::CreateLongPolling()
{
	this->m_long_poll = std::make_unique<TgBot::TgLongPoll>(*this->m_bot);
}

inline void TelegramBotTagging::DisplayMessageOfNumberOfCanceledRequestsOnConsole(const std::string_view message) noexcept
{
	std::cout << message << std::endl;
}

inline void TelegramBotTagging::SaveMessageOfNumberOfCanceledRequestsInLog(const std::string_view message)
{
	this-> m_logger->AppendProgramStatusData(message);
}

inline void TelegramBotTagging::RemoveDuplicateGroupIds(T_GroupIds *group_ids)
{
	std::sort(group_ids->begin(), group_ids->end());
	(void)group_ids->erase(std::unique(group_ids->begin(), group_ids->end()), group_ids->end());
}
}  // namespace N_TelegramBotTagging

#endif  // TELEGRAM_BOT_TAGGING_HPP
