// Copyright [2023] <Volodymyr Dorozhovets>"

#ifndef CONSOLE_INTERFACE_HPP
#define CONSOLE_INTERFACE_HPP

#include <string_view>

#include "logger.hpp"
#include "user_data.hpp"


namespace N_TelegramBotTagging
{
class ConsoleInterface
{
public:
	inline static constexpr std::string_view S_DEFAULT_FILE_WITH_API_TOKEN{"config/api_token.txt"};
public:
	inline explicit ConsoleInterface(Logger *logger);

	UserData InteractWithUser();
private:
	Logger *m_logger;
private:
	static bool TryReadingApiTokenFromFile(std::string *api_token);

	static std::string ReadingApiTokenFromConsole() noexcept;

	static bool AskUserToSaveApiToken();

	void SaveApiTokenInFile(std::string_view api_token);

	static void DisplayInformation() noexcept;
};
inline ConsoleInterface::ConsoleInterface(Logger *logger)
	: m_logger(logger)
{
}
}  // namespace N_TelegramBotTagging

#endif  // CONSOLE_INTERFACE_HPP
