// Copyright [2023] <Volodymyr Dorozhovets>"

#ifndef COMMAND_CALLBACK_SETTINGS_HPP
#define COMMAND_CALLBACK_SETTINGS_HPP

#include "logger.hpp"
#include "bot_info.hpp"
#include "manager/database.hpp"


namespace N_TelegramBotTagging::N_Command::N_Callback
{
class Settings
{
public:
	inline explicit Settings(TgBot::Bot 		 *bot,
							 Logger 	   		 *logger,
							 N_Database::Manager *database_manager);

	void operator()(const TgBot::CallbackQuery::Ptr &callback_query);
private:
	inline static constexpr std::string_view S_COLUMN{"selected"};
private:
	TgBot::Bot 	  		*m_bot;
	Logger 	      		*m_logger;
	N_Database::Manager *m_database_manager;

	std::string m_table_name;
private:
	void SendUpdatedSettingsToSelectUsersForTagging(const TgBot::CallbackQuery::Ptr &callback_query);

	void HandleButtons(int64_t group_id,
					   std::string_view callback_data);

	void HandleDefaultButton();

	void HandleUserButton(std::string_view callback_data);
};

inline Settings::Settings(TgBot::Bot 		  *bot,
						  Logger 	   		  *logger,
						  N_Database::Manager *database_manager)
	: m_bot	  			(bot	 		 ),
	  m_logger			(logger			 ),
	  m_database_manager(database_manager)
{
}
}  // namespace N_TelegramBotTagging::N_Command::N_Callback

#endif  // COMMAND_CALLBACK_SETTINGS_HPP
