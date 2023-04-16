// Copyright [2023] <Volodymyr Dorozhovets>"

#if defined(_WIN32)
#include "framework.hpp"
#endif

#include "command/utilities.hpp"
#include "utilities.hpp"
#include "exception/has_no_selected_users_for_tagging.hpp"


namespace N_TelegramBotTagging::N_Command
{
std::string Utilities::CreateTextOfSelectedUsersToTagging()
{
	this->InitializeData();

	constexpr std::string_view condition{"selected == true"};
	auto users_first_names = this->GetUsersFirstNames(condition);

	if(users_first_names.empty())
	{
		throw N_Exception::HasNoSelectedUsersForTagging("Has no selected users for tagging!");
	}

	std::string selected_users = N_Utilities::ConcatenateVectorIntoSingleString(users_first_names);
	std::string text{"Selected users for tagging: \n"};

	text += selected_users;

	return text;
}

TgBot::InlineKeyboardMarkup::Ptr Utilities::CreateKeyboardToSelectUsersForTagging()
{
	this->InitializeData();

	TgBot::InlineKeyboardMarkup::Ptr keyboard(std::make_shared<TgBot::InlineKeyboardMarkup>());

	this->CreateBasicKeyboard(&keyboard);
	Utilities::CreateDefaultKeyboard(&keyboard);

	return keyboard;
}

void Utilities::HandleChatType(const TgBot::Chat::Ptr &chat)
{
	if(this->IsGroup(chat))
	{
		this->TryCreateUsersTable(this->m_group_id);
	}
	else
	{
		(void)this->TryAddIdToGroupsTable(this->m_group_id);
	}
}

void Utilities::SendDefaultMessageIfNotGroups(const TgBot::Bot &bot)
{
	const auto result
		{bot.getApi().sendMessage(this->m_group_id, Utilities::S_DEFAULT_MESSAGE_IF_NOT_GROUPS.data())};

	if(result == nullptr)
	{
		std::string error_message{"TelegramBotTagging: can't send message if not groups for group id: "};
		error_message += std::to_string(this->m_group_id);

		throw std::runtime_error(error_message);
	}
}

void Utilities::SendDefaultMessageIfHasNoRegisteredOrSelectedUsers(const int64_t group_id, const TgBot::Bot &m_bot)
{
	const auto result{m_bot.getApi().sendMessage(group_id, Utilities::S_DEFAULT_MESSAGE_IF_HAS_NO_REGISTERED_OR_SELECTED_USERS.data())};

	if(result == nullptr)
	{
		std::string error_message{"TelegramBotTagging: can't send message if has no registered or selected users for group id: "};
		error_message += std::to_string(group_id);

		throw std::runtime_error(error_message);
	}
}

void Utilities::CreateBasicKeyboard(TgBot::InlineKeyboardMarkup::Ptr *basic_keyboard)
{
	auto users_first_names = this->GetUsersFirstNames();
	auto user_ids 		   = this->GetUsersIds		 ();

	constexpr std::size_t default_number_of_buttons_per_row{4UL};
	const std::size_t number_of_user_ids{user_ids.size()};

	std::size_t i{0UL};
	while(i < number_of_user_ids)
	{
		std::vector<TgBot::InlineKeyboardButton::Ptr> buttons;
		buttons.reserve(default_number_of_buttons_per_row);
		for (std::size_t k{0UL}; k < default_number_of_buttons_per_row and i < number_of_user_ids; ++k)
		{
			std::string user_id = user_ids[i];
			TgBot::InlineKeyboardButton::Ptr button(std::make_shared<TgBot::InlineKeyboardButton>());
			button->text = users_first_names[i];
			button->callbackData = user_id;
			(void)buttons.emplace_back(button);
			++i;
		}
		(void)(*basic_keyboard)->inlineKeyboard.emplace_back(buttons);
	}
}

inline std::vector<std::string> Utilities::GetUsersIds(const std::string_view condition)
{
	constexpr std::string_view column{"id"};

	auto result{this->m_database_manager->GetDataFromTableUnderCondition<std::string>(this->m_table_name,
																					  column,
																					  condition)};

	return result;
}

void Utilities::CreateDefaultKeyboard(TgBot::InlineKeyboardMarkup::Ptr *default_keyboard)
{
	std::vector< TgBot::InlineKeyboardButton::Ptr > buttons;
	TgBot::InlineKeyboardButton::Ptr default_button{std::make_shared<TgBot::InlineKeyboardButton>()};

	default_button->text         = "Default";
	default_button->callbackData = "Default";

	(void)buttons.emplace_back(default_button);

	(*default_keyboard)->inlineKeyboard.push_back(buttons);
}

inline void Utilities::TryCreateUsersTable(const int64_t group_id)
{
	const bool result{this->TryAddIdToGroupsTable(group_id)};

	if(result)
	{
		this->m_database_manager->CreateUsersTable(group_id);
	}
}

bool Utilities::TryAddIdToGroupsTable(const int64_t group_id)
{
	const bool id_added{this->m_database_manager->CheckIfIdAddedToTable("groups", group_id)};

	if(not id_added)
	{
		const N_Database::N_Tables::Groups groups{group_id};
		this->m_database_manager->AddDataToGroupsTable(groups);
	}

	return not id_added;
}
}  // namespace N_TelegramBotTagging::N_Command
