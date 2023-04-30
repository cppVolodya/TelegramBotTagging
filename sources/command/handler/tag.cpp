// Copyright [2023] <Volodymyr Dorozhovets>"

#if defined(_WIN32)
#include "framework.hpp"
#endif

#include "command/handler/tag.hpp"
#include "increment_decrement_pending_requests.hpp"
#include "command/utilities.hpp"
#include "utilities.hpp"


namespace N_TelegramBotTagging::N_Command::N_Handler
{
void Tag::operator()(const TgBot::Message::Ptr &message)
{
	Utilities utilities{this->m_database_manager, message->chat->id};

	const auto &chat = message->chat;
	utilities.HandleChatType(chat);

	IncrementDecrementPendingRequests increment_decrement_pending_requests
		{message->chat->id, this->m_database_manager};

	this->m_logger->AppendUsersRequestsData(message, BotInfo::S_DEFAULT_COMMANDS[4UL].first);

	const bool is_group = Utilities::IsGroup(chat);
	if(not is_group)
	{
		utilities.SendDefaultMessageIfNotGroups(*this->m_bot);
	}
	else
	{
		this->MentionSelectedUsersInGroup(message);
	}

	increment_decrement_pending_requests.Decrement();
}

void Tag::MentionSelectedUsersInGroup(const TgBot::Message::Ptr &message)
{
	const int64_t 	  group_id	{message->chat->id			 };
	const std::string users_tags{this->GetUsersTags(group_id)};

	if(not users_tags.empty())
	{
		const std::string user_text {Tag::GetUserText(message)	 };
		this->SendMessageToGroup(group_id,
								 users_tags,
								 user_text);
	}
	else
	{
		Utilities::SendDefaultMessageIfHasNoRegisteredOrSelectedUsers(group_id, *this->m_bot);
	}
}

inline std::string Tag::GetUsersTags(const int64_t group_id)
{
	const std::string table_name		{N_Database::Manager::GetTableNameUsersByGroupId(group_id)};
	constexpr std::string_view column	{"tag"												      };
	constexpr std::string_view condition{"selected == true"										  };

	const auto vector_users_tags{m_database_manager->GetDataFromTableUnderCondition<std::string>(table_name,
																								 column,
																								 condition)};

	std::string string_users_tags{N_Utilities::ConcatenateVectorIntoSingleString(vector_users_tags)};

	return string_users_tags;
}

inline std::string Tag::GetUserText(const TgBot::Message::Ptr &message)
{
	std::string user_text{message->text};

	const std::size_t position{user_text.find_first_of(' ')};
	if(position != std::string::npos)
	{
		user_text = user_text.substr(position + 1UL);
	}
	else
	{
		user_text.clear();
	}

	return user_text;
}

void Tag::SendMessageToGroup(const int64_t group_id,
							 const std::string_view users_tags,
							 const std::string_view user_text)
{
	std::string message{user_text};
	message += "\n";
	message += users_tags;

	const auto result{this->m_bot->getApi().sendMessage(group_id,
														message,
														false,
														0,
														std::make_shared<TgBot::GenericReply>(),
														"Markdown")};

	if(result == nullptr)
	{
		std::string error_message{"TelegramBotTagging: can't send message to group id: "};
		error_message += std::to_string(group_id);

		throw std::runtime_error(error_message);
	}
}
}  // namespace N_TelegramBotTagging::N_Command::N_Handler
