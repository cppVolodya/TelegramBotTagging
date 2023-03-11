// Copyright [2023] <Volodymyr Dorozhovets>"

#ifndef EXCEPTION_HAS_NO_SELECTED_USERS_FOR_TAGGING_HPP
#define EXCEPTION_HAS_NO_SELECTED_USERS_FOR_TAGGING_HPP

#include <stdexcept>


namespace N_TelegramBotTagging::N_Exception
{
class HasNoSelectedUsersForTagging : public std::runtime_error
{
public:
	inline explicit HasNoSelectedUsersForTagging(const std::string &message);
};

inline HasNoSelectedUsersForTagging::HasNoSelectedUsersForTagging(const std::string &message)
	: std::runtime_error(message)
{
}
}  // namespace N_TelegramBotTagging::N_Exception

#endif  // EXCEPTION_HAS_NO_SELECTED_USERS_FOR_TAGGING_HPP
