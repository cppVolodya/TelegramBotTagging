// Copyright [2023] <Volodymyr Dorozhovets>"

#ifndef ERROR_FLAGS_HPP
#define ERROR_FLAGS_HPP

namespace N_TelegramBotTagging::N_Error
{
enum class Flags
{
	minor       = 1,
	error       = 2,
	critical    = 4,
	unspecified = 8
};
}  // N_TelegramBotTagging::N_Error

#endif  // ERROR_FLAGS_HPP
