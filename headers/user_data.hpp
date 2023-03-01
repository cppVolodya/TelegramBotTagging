// Copyright [2023] <Volodymyr Dorozhovets>"

#ifndef USER_DATA_HPP
#define USER_DATA_HPP

#include <utility>

#include "bot_info.hpp"


namespace N_TelegramBotTagging
{
class UserData
{
public:
	inline explicit UserData(BotInfo bot_info = BotInfo()) noexcept;

	[[nodiscard]] inline BotInfo& GetBotInfo() noexcept;
private:
	BotInfo m_bot_info;
};

inline UserData::UserData(BotInfo bot_info) noexcept
	: m_bot_info(std::move(bot_info))
{
}

[[nodiscard]] inline BotInfo& UserData::GetBotInfo() noexcept
{
	return m_bot_info;
}
}  // namespace N_TelegramBotTagging

#endif  // USER_DATA_HPP
