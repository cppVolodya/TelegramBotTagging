// Copyright [2023] <Volodymyr Dorozhovets>"

#if defined(_WIN32)
#include "framework.hpp"
#endif

#include "command/handler/start.hpp"
#include "increment_decrement_pending_requests.hpp"
#include "command/utilities.hpp"


namespace N_TelegramBotTagging::N_Command::N_Handler
{
void Start::operator()(const TgBot::Message::Ptr &message)
{
	Utilities utilities{this->m_database_manager, message->chat->id};

	const auto &chat = message->chat;
	utilities.HandleChatType(chat);

	IncrementDecrementPendingRequests increment_decrement_pending_requests
		{message->chat->id, this->m_database_manager};

	this->m_logger->AppendUsersRequestsData(message, BotInfo::S_DEFAULT_COMMANDS[0UL].first);

	const bool is_group = Utilities::IsGroup(chat);
	if(not is_group)
	{
		utilities.SendDefaultMessageIfNotGroups(*this->m_bot);
	}

	this->SendGeneralInformationAboutBot(message);

	increment_decrement_pending_requests.Decrement();
}

void Start::SendGeneralInformationAboutBot(const TgBot::Message::Ptr &message)
{
	constexpr std::string_view photo_file_path{BotInfo::S_DEFAULT_DESCRIPTION_PICTURE};
	constexpr std::string_view photo_mime_type = "image/png";

	auto result {this->m_bot->getApi().sendPhoto(message->chat->id,
												 TgBot::InputFile::fromFile(photo_file_path.data(), photo_mime_type.data()),
												 Start::S_GENERAL_INFORMATION)};

	if (result == nullptr)
	{
		std::string error_message{"TelegramBotTagging: can't send general information about bot for group id: "};
		error_message += std::to_string(message->chat->id);

		throw std::runtime_error(error_message);
	}
}
}  // namespace N_TelegramBotTagging::N_Command::N_Handler
