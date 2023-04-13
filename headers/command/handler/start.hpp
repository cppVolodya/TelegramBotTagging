// Copyright [2023] <Volodymyr Dorozhovets>"

#ifndef COMMAND_HANDLER_START_HPP
#define COMMAND_HANDLER_START_HPP

#include "logger.hpp"
#include "bot_info.hpp"
#include "manager/database.hpp"


namespace N_TelegramBotTagging::N_Command::N_Handler
{
class Start
{
public:
	inline explicit Start(TgBot::Bot 		  *bot,
						  Logger 	   		  *logger,
						  N_Database::Manager *database_manager);

	void operator()(const TgBot::Message::Ptr &message);
private:
	inline static const std::string S_GENERAL_INFORMATION
		{"Firstname: "     + std::string(BotInfo::S_DEFAULT_FIRSTNAME)     + "\n" +
		 "Username: "      + std::string(BotInfo::S_DEFAULT_USERNAME)      + "\n" +
		 "About: " 	       + std::string(BotInfo::S_DEFAULT_ABOUT)         + "\n" +
		 "Description: "   + std::string(BotInfo::S_DEFAULT_DESCRIPTION)   + "\n" +
		 "Group privacy: " + std::string(BotInfo::S_DEFAULT_GROUP_PRIVACY) + "\n" +
		 "Commands:\n"
		 "/" + std::string(BotInfo::S_DEFAULT_COMMANDS[0UL].first) + " - " + std::string(BotInfo::S_DEFAULT_COMMANDS[0UL].second) + "\n"
		 "/" + std::string(BotInfo::S_DEFAULT_COMMANDS[1UL].first) + " - " + std::string(BotInfo::S_DEFAULT_COMMANDS[1UL].second) + "\n"
		 "/" + std::string(BotInfo::S_DEFAULT_COMMANDS[2UL].first) + " - " + std::string(BotInfo::S_DEFAULT_COMMANDS[2UL].second) + "\n"
		 "/" + std::string(BotInfo::S_DEFAULT_COMMANDS[3UL].first) + " - " + std::string(BotInfo::S_DEFAULT_COMMANDS[3UL].second) + "\n"
		 "/" + std::string(BotInfo::S_DEFAULT_COMMANDS[4UL].first) + " - " + std::string(BotInfo::S_DEFAULT_COMMANDS[4UL].second)};
private:
	TgBot::Bot 	  		*m_bot;
	Logger 	      		*m_logger;
	N_Database::Manager *m_database_manager;
private:
	void SendGeneralInformationAboutBot(const TgBot::Message::Ptr &message);
};

inline Start::Start(TgBot::Bot 		    *bot,
					Logger 	   		    *logger,
					N_Database::Manager *database_manager)
	: m_bot	  			(bot	 		 ),
	  m_logger			(logger			 ),
	  m_database_manager(database_manager)
{
}
}  // namespace N_TelegramBotTagging::N_Command::N_Handler

#endif  // COMMAND_HANDLER_START_HPP
