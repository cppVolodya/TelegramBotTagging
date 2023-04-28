// Copyright [2023] <Volodymyr Dorozhovets>"

#ifndef COMMAND_HANDLER_TAG_HPP
#define COMMAND_HANDLER_TAG_HPP

#include "logger.hpp"
#include "bot_info.hpp"
#include "manager/database.hpp"


namespace N_TelegramBotTagging::N_Command::N_Handler
{
class Tag
{
public:
	inline explicit Tag(TgBot::Bot 		    *bot,
						Logger 	   		    *logger,
						N_Database::Manager *database_manager);

	void operator()(const TgBot::Message::Ptr &message);
private:
	TgBot::Bot 	  		*m_bot;
	Logger 	      		*m_logger;
	N_Database::Manager *m_database_manager;
private:
	void MentionSelectedUsersInGroup(const TgBot::Message::Ptr &message);

	inline std::string GetUsersTags(int64_t group_id);

	static std::string GetUserText(const TgBot::Message::Ptr &message);

	void SendMessageToGroup(int64_t 		 group_id,
							std::string_view users_tags,
							std::string_view user_text);
};

inline Tag::Tag(TgBot::Bot 		        *bot,
					Logger 	   		    *logger,
					N_Database::Manager *database_manager)
	: m_bot	  			(bot	 		 ),
	  m_logger			(logger			 ),
	  m_database_manager(database_manager)
{
}
}  // namespace N_TelegramBotTagging::N_Command::N_Handler

#endif  // COMMAND_HANDLER_TAG_HPP
