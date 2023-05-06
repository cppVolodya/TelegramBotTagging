// Copyright [2023] <Volodymyr Dorozhovets>"

#if defined(_WIN32)
#include "framework.hpp"
#endif

#include "command/callback/settings.hpp"
#include "increment_decrement_pending_requests.hpp"
#include "command/utilities.hpp"
#include "exception/has_no_selected_users_for_tagging.hpp"


namespace N_TelegramBotTagging::N_Command::N_Callback
{
void Settings::operator()(const TgBot::CallbackQuery::Ptr &callback_query)
{
	const auto message{callback_query->message};
	Utilities utilities{this->m_database_manager, message->chat->id};

	const auto &chat = message->chat;
	utilities.HandleChatType(chat);

	IncrementDecrementPendingRequests increment_decrement_pending_requests
		{message->chat->id, this->m_database_manager};

	this->m_logger->AppendUsersRequestsData(message, "settings::callback");

	const bool is_group = Utilities::IsGroup(chat);
	if(not is_group)
	{
		utilities.SendDefaultMessageIfNotGroups(*this->m_bot);
	}

	this->SendUpdatedSettingsToSelectUsersForTagging(callback_query);

	increment_decrement_pending_requests.Decrement();
}

void Settings::SendUpdatedSettingsToSelectUsersForTagging(const TgBot::CallbackQuery::Ptr &callback_query)
{
	const int64_t 	  group_id	   {callback_query->message->chat->id};
	const std::string callback_data{callback_query->data			 };
	this->HandleButtons(group_id, callback_data);

	Utilities utilities(m_database_manager, group_id);
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

	try
	{
		const auto result{this->m_bot->getApi().editMessageText(text, group_id,
															   callback_query->message->messageId,
															   "", "", false, keyboard)};

		if(result == nullptr)
		{
			std::string  error_message{"TelegramBotTagging: can't send updated settings to select users for tagging for group id: "};
			error_message += std::to_string(group_id);

			throw std::runtime_error(error_message);
		}
	}
	catch(TgBot::TgException & exception)
	{
		constexpr std::string_view duplicated_content_error_message
			{"Bad Request: message is not modified: specified new message content and "
			 "reply markup are exactly the same as a current content and reply markup of the message"};

		if(exception.what() != duplicated_content_error_message)
		{
			throw;
		}
	}
}

void Settings::HandleButtons(const int64_t group_id,
							 const std::string_view callback_data)
{
	this->m_table_name = this->m_database_manager->GetTableNameUsersByGroupId(group_id);

	if(callback_data == "Default")
	{
		this->HandleDefaultButton();
	}
	else
	{
		this->HandleUserButton(callback_data);
	}
}

void Settings::HandleDefaultButton()
{
	constexpr bool value{true};

	this->m_database_manager->UpdateValueInTable(m_table_name,
												 Settings::S_COLUMN,
												 value);
}

void Settings::HandleUserButton(const std::string_view callback_data)
{
	std::string condition{"id = "};
	condition += callback_data;

	const auto user_id
		= this->m_database_manager->GetDataFromTableUnderCondition<int64_t>(m_table_name,
																			Settings::S_COLUMN,
																			condition);

	const bool value{not static_cast<bool>(user_id[0UL])};

	this->m_database_manager->UpdateValueInTable(m_table_name,
												 Settings::S_COLUMN,
												 value,
												 condition);
}
}  // namespace N_TelegramBotTagging::N_Command::N_Callback
