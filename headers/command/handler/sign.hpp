// Copyright [2023] <Volodymyr Dorozhovets>"

#ifndef COMMAND_HANDLER_SIGN_HPP
#define COMMAND_HANDLER_SIGN_HPP

#include "logger.hpp"
#include "bot_info.hpp"
#include "manager/database.hpp"


namespace N_TelegramBotTagging::N_Command::N_Handler
{
class Sign
{
public:
	inline explicit Sign(TgBot::Bot 		 *bot,
						 Logger 	   		 *logger,
						 N_Database::Manager *database_manager);

	void operator()(const TgBot::Message::Ptr &message);
private:
	TgBot::Bot 	  		*m_bot;
	Logger 	      		*m_logger;
	N_Database::Manager *m_database_manager;
private:
	void RegisterUserInDatabase(const TgBot::Message::Ptr &message);

	void SendFailureMessage(const TgBot::Message::Ptr &message);

	void AddUserToDatabase(const TgBot::Message::Ptr &message);

	static std::string CreateTagForUser(const TgBot::Message::Ptr &message);

	static std::string GetUniqueUsername(const TgBot::Message::Ptr &message) noexcept;

	void SendSuccessMessage(const TgBot::Message::Ptr &message);
};
inline Sign::Sign(TgBot::Bot 		  *bot,
				  Logger 	   		  *logger,
				  N_Database::Manager *database_manager)
	: m_bot	  			(bot	 		 ),
	  m_logger			(logger			 ),
	  m_database_manager(database_manager)
{
}
}  // namespace N_TelegramBotTagging::N_Command::N_Handler

#endif  // COMMAND_HANDLER_SIGN_HPP
