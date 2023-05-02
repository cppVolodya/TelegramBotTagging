// Copyright [2023] <Volodymyr Dorozhovets>"

#if defined(_WIN32)
#include "framework.hpp"
#endif

#include "command/handler/settings.hpp"
#include "increment_decrement_pending_requests.hpp"
#include "command/utilities.hpp"
#include "exception/has_no_selected_users_for_tagging.hpp"


namespace N_TelegramBotTagging::N_Command::N_Handler
{
void Settings::operator()(const TgBot::Message::Ptr &message)
{
	Utilities utilities{this->m_database_manager, message->chat->id};

	const auto &chat = message->chat;
	utilities.HandleChatType(chat);

	const int64_t group_id{message->chat->id};
	IncrementDecrementPendingRequests increment_decrement_pending_requests
		{group_id, this->m_database_manager};

	this->m_logger->AppendUsersRequestsData(message, BotInfo::S_DEFAULT_COMMANDS[2UL].first);

	const bool is_group = Utilities::IsGroup(chat);
	if(not is_group)
	{
		utilities.SendDefaultMessageIfNotGroups(*this->m_bot);
	}
	else
	{
		this->SendSettingsToSelectUsersForTagging(group_id);
	}

	increment_decrement_pending_requests.Decrement();
}

void Settings::SendSettingsToSelectUsersForTagging(const int64_t group_id)
{
	Utilities utilities(m_database_manager, group_id);

	if(utilities.IsRegisteredUsersToTagging())
	{
		std::string text;
		try
		{
			text = utilities.CreateTextOfSelectedUsersToTagging();
		}
		catch(const N_Exception::HasNoSelectedUsersForTagging &)
		{
			text = "No users selected to tagging!";
		}

		const auto keyboard{utilities.CreateKeyboardToSelectUsersForTagging()};

		const auto result{this->m_bot->getApi().sendMessage(group_id, text, false, 0, keyboard)};

		if (result == nullptr)
		{
			std::string
				error_message{"TelegramBotTagging: can't send settings to select users for tagging for group id: "};
			error_message += std::to_string(group_id);

			throw std::runtime_error(error_message);
		}
	}
	else
	{
		Utilities::SendDefaultMessageIfHasNoRegisteredOrSelectedUsers(group_id, *this->m_bot);
	}
}
}  // namespace N_TelegramBotTagging::N_Command::N_Handler
