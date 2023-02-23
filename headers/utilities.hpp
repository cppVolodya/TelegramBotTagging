// Copyright [2023] <Volodymyr Dorozhovets>"

#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <string>
#include <vector>


namespace N_TelegramBotTagging::N_Utilities
{
std::string ConcatenateVectorIntoSingleString(const std::vector<std::string> &vector);

std::string CreateMessageForExceptionErrorWritingDataToFile(std::string_view filename,
															std::string_view data);
}  // namespace N_TelegramBotTagging::N_Utilities

#endif  // UTILITIES_HPP
