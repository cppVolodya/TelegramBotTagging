// Copyright [2023] <Volodymyr Dorozhovets>"

#ifndef EXCEPTION_ERROR_WRITING_DATA_TO_ERROR_LOG_FILE_HPP
#define EXCEPTION_ERROR_WRITING_DATA_TO_ERROR_LOG_FILE_HPP

#include <stdexcept>


namespace N_TelegramBotTagging::N_Exception
{
class ErrorWritingDataToErrorLogFile : public std::runtime_error
{
public:
	inline explicit ErrorWritingDataToErrorLogFile(const std::string &message);
};

inline ErrorWritingDataToErrorLogFile::ErrorWritingDataToErrorLogFile(const std::string &message)
	: std::runtime_error(message)
{
}
}  // namespace N_TelegramBotTagging::N_Exception

#endif  // EXCEPTION_ERROR_WRITING_DATA_TO_ERROR_LOG_FILE_HPP
