// Copyright [2023] <Volodymyr Dorozhovets>"

#ifndef COMMAND_UTILITIES_HPP
#define COMMAND_UTILITIES_HPP

#include <string_view>

#include <tgbot/tgbot.h>

#include "manager/database.hpp"


namespace N_TelegramBotTagging::N_Command
{
class Utilities
{
public:
	explicit inline Utilities(N_Database::Manager *database_manager,
							  int64_t group_id);

	std::string CreateTextOfSelectedUsersToTagging();

	TgBot::InlineKeyboardMarkup::Ptr CreateKeyboardToSelectUsersForTagging();

	void HandleChatType(const TgBot::Chat::Ptr &chat);

	static bool IsGroup(const TgBot::Chat::Ptr &chat) noexcept;

	void SendDefaultMessageIfNotGroups(const TgBot::Bot &bot);

	static void SendDefaultMessageIfHasNoRegisteredOrSelectedUsers(int64_t group_id, const TgBot::Bot &bot);

	bool IsRegisteredUsersToTagging();
private:
	inline static constexpr std::string_view S_DEFAULT_MESSAGE_IF_NOT_GROUPS
		{"This is not a group or supergroup. Please, add me to a group and try again."};

	inline static constexpr std::string_view S_DEFAULT_MESSAGE_IF_HAS_NO_REGISTERED_OR_SELECTED_USERS
		{"WARNING! This chat does not appear to have any registered or selected users available for tagging."
		 "To successfully recall users, they must be registered with the Telegram bot using the /sign command."};
private:
	N_Database::Manager *m_database_manager;

	int64_t m_group_id;

	std::string m_table_name;
private:
	inline void InitializeData	   ();
	inline void InitializeTableName();

	inline std::vector<std::string> GetUsersIds		  (std::string_view condition = "");
	inline std::vector<std::string> GetUsersFirstNames(std::string_view condition = "");

	void CreateBasicKeyboard(TgBot::InlineKeyboardMarkup::Ptr *basic_keyboard);

	static void CreateDefaultKeyboard(TgBot::InlineKeyboardMarkup::Ptr *default_keyboard);

	inline void TryCreateUsersTable(int64_t group_id);

	bool TryAddIdToGroupsTable(int64_t group_id);
};
inline Utilities::Utilities(N_Database::Manager *database_manager,
					        int64_t group_id)
	: m_database_manager(database_manager),
	  m_group_id		(group_id		 )
{
}

inline bool Utilities::IsGroup(const TgBot::Chat::Ptr &chat) noexcept
{
	return (chat->type == TgBot::Chat::Type::Group     ) or
		   (chat->type == TgBot::Chat::Type::Supergroup);
}

inline bool Utilities::IsRegisteredUsersToTagging()
{
	this->InitializeData();

	auto users_first_names = this->GetUsersFirstNames();

	return not users_first_names.empty();
}

inline void Utilities::InitializeData()
{
	this->InitializeTableName();
}

inline void Utilities::InitializeTableName()
{
	if(this->m_table_name.empty())
	{
		this->m_table_name = this->m_database_manager->GetTableNameUsersByGroupId(this->m_group_id);
	}
}

inline std::vector<std::string> Utilities::GetUsersFirstNames(const std::string_view condition)
{
	constexpr std::string_view column{"first_name"};

	auto result
		{this->m_database_manager->GetDataFromTableUnderCondition<std::string>(this->m_table_name,
																			   column,
																			   condition)};

	return result;
}
}  // namespace N_TelegramBotTagging::N_Command

#endif  // COMMAND_UTILITIES_HPP
