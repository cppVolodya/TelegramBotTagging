// Copyright [2023] <Volodymyr Dorozhovets>"

#ifndef COMMAND_HANDLER_HELP_HPP
#define COMMAND_HANDLER_HELP_HPP

#include "logger.hpp"
#include "bot_info.hpp"
#include "manager/database.hpp"


namespace N_TelegramBotTagging::N_Command::N_Handler
{
class Help
{
public:
	inline explicit Help(TgBot::Bot 		 *bot,
						 Logger 	   		 *logger,
						 N_Database::Manager *database_manager);

	void operator()(const TgBot::Message::Ptr &message);
private:
	inline static constexpr std::string_view S_INSTRUCTIONS
		{"I am a TagBot created specifically for tagging or mentioning users in your group."
		 "With my features, you can easily reach many people at the same time and"
		 "inform them of important information.\n\n"

		 "Here is a list of available commands:\n\n"

		 "/start - this command allows you to get general information about the bot."
		 "You will receive information such as: firstname, username, about, description, group privacy,"
		 "commands(as well as a brief description of each command) and description picture.\n\n"

		 "/help - This command provides you with detailed help and instructions for using the bot."
		 "You will learn about all the available commands and their purpose in a broad description.\n\n"

		 "/settings - with this command you can select the users you want to tag."
		 "A list of selected users to tag or mention will be provided and"
		 "a panel will open where you can select users by clicking on buttons,"
		 "clicking on a specific user will automatically add or remove it from the list."
		 "A \"Default\" button will also be available, which will perform the function of resetting the default settings,"
		 "that is, all registered users will be selected for tagging.\n\n"

		 "/sign - This command allows you to log into the bot."
		 "With the help of this command, you can be tagged or mentioned in the group.\n\n"

		 "/tag [text] - This command allows you to tag all selected users with or without text."
		 "Just type /tag and then optionally type the text you want to include in the message to be tagged.\n\n"

		 "These are just a few basic commands I run. I am ready to help you with tagging and mentioning users in your group."};
private:
	TgBot::Bot 	  		*m_bot;
	Logger 	      		*m_logger;
	N_Database::Manager *m_database_manager;
private:
	void SendInstructionsForUsingBot(const TgBot::Message::Ptr &message);
};
inline Help::Help(TgBot::Bot 		  *bot,
				  Logger 	   		  *logger,
				  N_Database::Manager *database_manager)
	: m_bot	  			(bot	 		 ),
	  m_logger			(logger			 ),
	  m_database_manager(database_manager)
{
}
}  // namespace N_TelegramBotTagging::N_Command::N_Handler

#endif  // COMMAND_HANDLER_HELP_HPP
