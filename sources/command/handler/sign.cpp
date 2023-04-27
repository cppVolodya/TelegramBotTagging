// Copyright [2023] <Volodymyr Dorozhovets>"

#if defined(_WIN32)
#include "framework.hpp"
#endif

#include "command/handler/sign.hpp"
#include "increment_decrement_pending_requests.hpp"
#include "command/utilities.hpp"


namespace N_TelegramBotTagging::N_Command::N_Handler
{
void Sign::operator()(const TgBot::Message::Ptr &message)
{
	Utilities utilities{this->m_database_manager, message->chat->id};

	const auto &chat = message->chat;
	utilities.HandleChatType(chat);

	IncrementDecrementPendingRequests increment_decrement_pending_requests
		{message->chat->id, this->m_database_manager};

	this->m_logger->AppendUsersRequestsData(message, BotInfo::S_DEFAULT_COMMANDS[3UL].first);

	const bool is_group = Utilities::IsGroup(chat);
	if(not is_group)
	{
		utilities.SendDefaultMessageIfNotGroups(*this->m_bot);
	}
	else
	{
		this->RegisterUserInDatabase(message);
	}

	increment_decrement_pending_requests.Decrement();
}

void Sign::RegisterUserInDatabase(const TgBot::Message::Ptr &message)
{
	const int64_t group_id{message->chat->id};
	const std::string table_name{N_Database::Manager::GetTableNameUsersByGroupId(group_id)};

	bool id_added{m_database_manager->CheckIfIdAddedToTable(table_name, message->from->id)};
	if(id_added)
	{
		this->SendFailureMessage(message);
	}
	else
	{
		this->AddUserToDatabase(message);
	}
}

void Sign::SendFailureMessage(const TgBot::Message::Ptr &message)
{
	std::string failure_message{"You are already registered: "};
	failure_message += message->from->firstName;

	const auto result{this->m_bot->getApi().sendMessage(message->chat->id, failure_message)};

	if(result == nullptr)
	{
		std::string error_message{"TelegramBotTagging: can't send failure message for group id: "};
		error_message += std::to_string(message->chat->id);

		throw std::runtime_error(error_message);
	}
}

void Sign::AddUserToDatabase(const TgBot::Message::Ptr &message)
{
	const int64_t user_id			{message->from->id				};
	const std::string user_tag		{Sign::CreateTagForUser(message)};
	const std::string user_firstname{message->from->firstName		};

	N_Database::N_Tables::Users users{user_id, user_tag, user_firstname};

	this->m_database_manager->AddDataToUsersTable
		(this->m_database_manager->GetTableNameUsersByGroupId(message->chat->id), users);

	this->SendSuccessMessage(message);
}

std::string Sign::CreateTagForUser(const TgBot::Message::Ptr &message)
{
	const std::string unique_username{Sign::GetUniqueUsername(message)};
	const int64_t user_id{message->from->id};
	std::string user_tag{"["};
	user_tag += unique_username;
	user_tag += "](tg://user?id=";
	user_tag += std::to_string(user_id);
	user_tag += ")";

	return user_tag;
}

std::string Sign::GetUniqueUsername(const TgBot::Message::Ptr &message) noexcept
{
	std::string unique_username{message->from->username};
	if(unique_username.empty())
	{
		unique_username = message->from->firstName;
	}

	return unique_username;
}

void Sign::SendSuccessMessage(const TgBot::Message::Ptr &message)
{
	std::string success_message{"You have successfully registered: "};
	success_message += message->from->firstName;

	const auto result{this->m_bot->getApi().sendMessage(message->chat->id, success_message)};

	if(result == nullptr)
	{
		std::string error_message{"TelegramBotTagging: can't send success message for group id: "};
		error_message += std::to_string(message->chat->id);

		throw std::runtime_error(error_message);
	}
}
}  // namespace N_TelegramBotTagging::N_Command::N_Handler
