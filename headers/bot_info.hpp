// Copyright [2023] <Volodymyr Dorozhovets>"

#ifndef BOT_INFO_HPP
#define BOT_INFO_HPP

#include <string_view>
#include <string>
#include <array>
#include <utility>


namespace N_TelegramBotTagging
{
class BotInfo
{
public:
	using command			  = std::string_view;
	using command_description = std::string_view;
public:
	inline static constexpr std::string_view S_DEFAULT_FIRSTNAME{"TagBot"};

	inline static constexpr std::string_view S_DEFAULT_USERNAME{"tag_cpp_bot"};

	inline static constexpr std::string_view S_DEFAULT_ABOUT{"This bot is designed to mention or tag users in a group."};

	inline static constexpr std::string_view S_DEFAULT_DESCRIPTION
		{"This Telegram bot provides a simple and effective feature to mention or tag users in a group. "
		 "It will further increase organization and simplify communication, "
		 "allowing you to quickly address selected groups of participants."};

	inline static constexpr std::string_view S_DEFAULT_DESCRIPTION_PICTURE{"images/description_picture_for_bot.png"};

	inline static constexpr std::string_view S_DEFAULT_GROUP_PRIVACY{"Privacy mode is on."};

	inline static constexpr unsigned int S_DEFAULT_NUMBER_OF_COMMANDS{5U};

	inline static constexpr std::array<std::pair<command, command_description>, S_DEFAULT_NUMBER_OF_COMMANDS> S_DEFAULT_COMMANDS
		{std::pair("start", "Get general information about the bot."),
		 std::pair("help", "Get help and instructions for using the bot."),
		 std::pair("settings", "Sign in to the bot."),
		 std::pair("sign", "Sign in to the bot."),
		 std::pair("tag", "Tag all selected users with or without text: /tag [text].")};
public:
	explicit inline BotInfo(std::string_view api_token = "") noexcept;

	inline void SetApiToken(std::string_view api_token) noexcept;

	[[nodiscard]] inline std::string GetApiToken() const noexcept;
private:
	std::string m_api_token;
};
inline BotInfo::BotInfo(const std::string_view api_token) noexcept
	: m_api_token(api_token)
{
}

inline void BotInfo::SetApiToken(const std::string_view api_token) noexcept
{
	m_api_token = api_token;
}

[[nodiscard]] inline std::string BotInfo::GetApiToken() const noexcept
{
	return m_api_token;
}
}  // namespace N_TelegramBotTagging

#endif  // BOT_INFO_HPP
