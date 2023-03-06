// Copyright [2023] <Volodymyr Dorozhovets>"

#ifndef ERROR_MESSAGES_HPP
#define ERROR_MESSAGES_HPP

#include <string_view>


namespace N_TelegramBotTagging::N_Error::N_Messages
{
inline static constexpr std::string_view G_LOG_FILE_HINT
	{"Maybe look at the log file called 'errors.log' to learn more about the type of error."};

inline static constexpr std::string_view G_MINOR
	{"A minor error has occurred in the program. The program continues its work."};

inline static constexpr std::string_view G_ERROR
	{"An error occurred in the program. The program will be completed."};

inline static constexpr std::string_view G_CRITICAL
	{"The program has encountered a critical failure. The program will be completed."};

inline static constexpr std::string_view G_UNSPECIFIED
	{"An unspecified error occurred in the program. The program will be completed."};
}  // namespace N_TelegramBotTagging::N_Error::N_Messages

#endif  // ERROR_MESSAGES_HPP
