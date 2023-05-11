// Copyright [2023] <Volodymyr Dorozhovets>"

#if defined(_WIN32)
#include "framework.hpp"
#endif

#include <numeric>

#include "telegram_bot_tagging.hpp"
#include "console_interface.hpp"
#include "bot_info.hpp"


namespace N_TelegramBotTagging
{
void TelegramBotTagging::operator()()
{
	ConsoleInterface console_interface(m_logger);
	UserData user_data{console_interface.InteractWithUser()};

	this->CreateBot(user_data.GetBotInfo().GetApiToken());
	this->CreateLongPolling();
	this->CreateCommandHandlers();

	const T_Requests requests{this->CancelAllRequests()};
	const std::string message{this->GetMessageOfNumberOfCanceledRequests(requests)};

	TelegramBotTagging::DisplayMessageOfNumberOfCanceledRequestsOnConsole(message);
	this->SaveMessageOfNumberOfCanceledRequestsInLog(message);

	const T_GroupIds group_ids{this->GetGroupIdsWithPendingRequests(requests)};
	this->InformGroupsOfServerIssues(group_ids);

	this->ClearPendingRequestsFromDatabase();

	this->InstallCommandHandlers();
	this->LaunchLongPolling();
}

void TelegramBotTagging::CreateCommandHandlers()
{
    this->m_start_command_handler 	  = std::make_unique<N_Command::N_Handler::Start>	 (this->m_bot.get(), this->m_logger, this->m_database_manager);
    this->m_help_command_handler 	  = std::make_unique<N_Command::N_Handler::Help> 	 (this->m_bot.get(), this->m_logger, this->m_database_manager);
    this->m_settings_command_handler  = std::make_unique<N_Command::N_Handler::Settings> (this->m_bot.get(), this->m_logger, this->m_database_manager);
    this->m_settings_command_callback = std::make_unique<N_Command::N_Callback::Settings>(this->m_bot.get(), this->m_logger, this->m_database_manager);
    this->m_sign_command_handler      = std::make_unique<N_Command::N_Handler::Sign>	 (this->m_bot.get(), this->m_logger, this->m_database_manager);
    this->m_tag_command_handler 	  = std::make_unique<N_Command::N_Handler::Tag>		 (this->m_bot.get(), this->m_logger, this->m_database_manager);
}

TelegramBotTagging::T_Requests TelegramBotTagging::CancelAllRequests()
{
	constexpr int limit  {100};
	constexpr int timeout{0  };
	TgBot::TgLongPoll temporary_long_poll(*this->m_bot, limit, timeout);

	T_Requests requests{this->m_bot->getApi().getUpdates()};

	const 	  std::size_t number_of_requests	{requests.size()};
	constexpr std::size_t min_number_of_requests{1UL			};

	if (number_of_requests == min_number_of_requests)
	{
		temporary_long_poll.start();
	}

	if (number_of_requests > min_number_of_requests)
	{
		temporary_long_poll.start();
		temporary_long_poll.start();
	}

	return requests;
}

std::string TelegramBotTagging::GetMessageOfNumberOfCanceledRequests(const T_Requests &requests)
{
	std::size_t number_of_requests{requests.size()};
	number_of_requests += GetTotalPendingRequestsFromDatabase();

	std::string message_rejected_request_count{"The number of canceled requests: "};
	message_rejected_request_count += std::to_string(number_of_requests);
	message_rejected_request_count += "\n";

	return message_rejected_request_count;
}

inline void TelegramBotTagging::ClearPendingRequestsFromDatabase()
{
	this->m_database_manager->UpdateValueInTable("groups", "number_pending_requests", "0");
}

std::size_t TelegramBotTagging::GetTotalPendingRequestsFromDatabase()
{
	constexpr std::string_view table	{"groups"					   };
	constexpr std::string_view column   {"number_pending_requests"	   };
	constexpr std::string_view condition{"number_pending_requests != 0"};

	const auto number_pending_requests
		{this->m_database_manager->GetDataFromTableUnderCondition<int>(table,
																	   column,
																	   condition)};

	auto total_pending_requests{std::accumulate(number_pending_requests.begin(),
												number_pending_requests.end  (), 0)};

	return static_cast<std::size_t>(total_pending_requests);
}

TelegramBotTagging::T_GroupIds TelegramBotTagging::GetGroupIdsWithPendingRequests(const T_Requests &requests)
{
	T_GroupIds group_ids_from_requests{TelegramBotTagging::GetGroupIdsFromRequests(requests)};

	T_GroupIds group_ids_from_database{this->GetGroupIdsFromDatabase()};

	T_GroupIds group_ids{TelegramBotTagging::MergeGroupIds(std::move(group_ids_from_requests),
														   std::move(group_ids_from_database))};

	TelegramBotTagging::RemoveDuplicateGroupIds(&group_ids);

	return group_ids;
}

TelegramBotTagging::T_GroupIds TelegramBotTagging::GetGroupIdsFromRequests(const T_Requests &requests)
{
	T_GroupIds group_ids;
	group_ids.reserve(requests.size());

	for (const auto &request : requests)
	{
		const int64_t group_id{request->message->chat->id};
		group_ids.push_back(group_id);
	}

	return group_ids;
}

TelegramBotTagging::T_GroupIds TelegramBotTagging::GetGroupIdsFromDatabase()
{
	constexpr std::string_view table    {"groups"				       };
	constexpr std::string_view column   {"id"						   };
	constexpr std::string_view condition{"number_pending_requests != 0"};

	auto group_ids{this->m_database_manager->GetDataFromTableUnderCondition<int64_t>(table,
																					 column,
																					 condition)};

	return group_ids;
}

TelegramBotTagging::T_GroupIds TelegramBotTagging::MergeGroupIds(T_GroupIds &&first_group_ids,
																 T_GroupIds &&second_group_ids)
{
	const std::size_t total_number_of_group_ids{first_group_ids.size() + second_group_ids.size()};

	T_GroupIds second_group_ids_moved{std::move(second_group_ids)};

	T_GroupIds merged_of_group_ids(std::move(first_group_ids));
	merged_of_group_ids.reserve(total_number_of_group_ids);
	(void)merged_of_group_ids.insert(merged_of_group_ids.end(),
									 second_group_ids_moved.begin(), second_group_ids_moved.end());

	return merged_of_group_ids;
}

void TelegramBotTagging::InformGroupsOfServerIssues(const T_GroupIds &group_ids)
{
	constexpr std::string_view message{"All your requests have been cancelled! "
									   "The server is currently rebooting or has experienced a temporary failure. "
									   "The server is back to normal. "
									   "Please try again your requests now. "
									   "Sorry for the temporary inconvenience and thank you for your understanding!"};

	for (const auto &group_id : group_ids)
	{
		auto result{this->m_bot->getApi().sendMessage(group_id, message.data())};
		if(result == nullptr)
		{
			std::string error_message{"TelegramBotTagging: "};
			error_message += "The message of '";
			error_message += message;
			error_message += "' could not be sent to the group with id: ";
			error_message += std::to_string(group_id);

			throw std::runtime_error(error_message);
		}
	}
}

void TelegramBotTagging::InstallCommandHandlers()
{
	this->InstallStartCommandHandler	();
	this->InstallHelpCommandHandler		();
	this->InstallSettingsCommandHandler ();
	this->InstallSettingsCommandCallback();
	this->InstallSignCommandHandler		();
	this->InstallTagCommandHandler		();
}

void TelegramBotTagging::InstallStartCommandHandler()
{
	this->m_bot->getEvents().onCommand(BotInfo::S_DEFAULT_COMMANDS[0UL].first.data(),
									   [&](const TgBot::Message::Ptr &message)
									   {
										   this->m_thread_pool->PushTask(this->m_start_command_handler.get(), message);
									   });
}

void TelegramBotTagging::InstallHelpCommandHandler()
{
	this->m_bot->getEvents().onCommand(BotInfo::S_DEFAULT_COMMANDS[1UL].first.data(),
									   [&](const TgBot::Message::Ptr &message)
									   {
										   this->m_thread_pool->PushTask(this->m_help_command_handler.get(), message);
									   });
}

void TelegramBotTagging::InstallSettingsCommandHandler()
{
	this->m_bot->getEvents().onCommand(BotInfo::S_DEFAULT_COMMANDS[2UL].first.data(),
									   [&](const TgBot::Message::Ptr &message)
									   {
											this->m_thread_pool->PushTask(this->m_settings_command_handler.get(), message);
									   });
}

void TelegramBotTagging::InstallSettingsCommandCallback()
{
	this->m_bot->getEvents().onCallbackQuery([&](const TgBot::CallbackQuery::Ptr &query)
											 {
												this->m_thread_pool->PushTask(this->m_settings_command_callback.get(), query);
											 });
}

void TelegramBotTagging::InstallSignCommandHandler()
{
	this->m_bot->getEvents().onCommand(BotInfo::S_DEFAULT_COMMANDS[3UL].first.data(),
									   [&](const TgBot::Message::Ptr &message)
									   {
										   this->m_thread_pool->PushTask(this->m_sign_command_handler.get(), message);
									   });
}

void TelegramBotTagging::InstallTagCommandHandler()
{
	this->m_bot->getEvents().onCommand(BotInfo::S_DEFAULT_COMMANDS[4UL].first.data(),
									   [&](const TgBot::Message::Ptr &message)
									   {
										   this->m_thread_pool->PushTask(this->m_tag_command_handler.get(), message);
									   });
}

void TelegramBotTagging::LaunchLongPolling()
{
	const bool &threading_enabled{m_thread_pool->IsThreadingEnabled()};
	std::cout << "The program started successfully\n" << std::endl;

	while(threading_enabled)
	{
		this->m_long_poll->start();
	}
}
}  // namespace N_TelegramBotTagging
