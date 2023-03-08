// Copyright [2023] <Volodymyr Dorozhovets>"

#ifndef EXCEPTION_THREAD_TIMEOUT_HPP
#define EXCEPTION_THREAD_TIMEOUT_HPP

#include <stdexcept>


namespace N_TelegramBotTagging::N_Exception
{
class ThreadTimeout : public std::runtime_error
{
public:
	inline explicit ThreadTimeout(const std::string &message);
};

inline ThreadTimeout::ThreadTimeout(const std::string &message)
	: std::runtime_error(message)
{
}
}  // namespace N_TelegramBotTagging::N_Exception

#endif  // EXCEPTION_THREAD_TIMEOUT_HPP
