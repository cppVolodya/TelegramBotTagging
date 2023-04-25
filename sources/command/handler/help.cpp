// Copyright [2023] <Volodymyr Dorozhovets>"

#if defined(_WIN32)
#include "framework.hpp"
#endif

#include "command/handler/help.hpp"
#include "increment_decrement_pending_requests.hpp"
#include "command/utilities.hpp"


namespace N_TelegramBotTagging::N_Command::N_Handler
{
void Help::operator()(const TgBot::Message::Ptr &message)
{
	Utilities utilities{this->m_database_manager, message->chat->id};

	const auto &chat = message->chat;
	utilities.HandleChatType(chat);

	IncrementDecrementPendingRequests increment_decrement_pending_requests
		{message->chat->id, this->m_database_manager};

	this->m_logger->AppendUsersRequestsData(message, BotInfo::S_DEFAULT_COMMANDS[1UL].first);

	const bool is_group = Utilities::IsGroup(chat);
	if(not is_group)
	{
		utilities.SendDefaultMessageIfNotGroups(*this->m_bot);
	}

	this->SendInstructionsForUsingBot(message);

	increment_decrement_pending_requests.Decrement();
}

void Help::SendInstructionsForUsingBot(const TgBot::Message::Ptr &message)
{
	const auto result{this->m_bot->getApi().sendMessage(message->chat->id, Help::S_INSTRUCTIONS.data())};

	if (result == nullptr)
	{
		std::string error_message{"TelegramBotTagging: can't send instructions for using bot for group id: "};
		error_message += std::to_string(message->chat->id);

		throw std::runtime_error(error_message);
	}
}
}  // namespace N_TelegramBotTagging::N_Command::N_Handler
