// Copyright [2023] <Volodymyr Dorozhovets>"

#if defined(_WIN32)
#include "framework.hpp"
#endif

#include <algorithm>
#include <cstring>
#include <stdexcept>

#include "utilities.hpp"


namespace N_TelegramBotTagging::N_Utilities
{
std::string ConcatenateVectorIntoSingleString(const std::vector<std::string> &vector)
{
	constexpr std::size_t approximate_string_size{5UL};
	const std::size_t minimum_size{vector.size() * approximate_string_size};
	std::string single_string;
	single_string.reserve(minimum_size);
	(void)std::for_each(vector.begin(), vector.end(),
						[&single_string](const std::string &string)
						{
							single_string += string;
							single_string += " ";
						});

	return single_string;
}

std::string CreateMessageForExceptionErrorWritingDataToFile(const std::string_view filename,
															const std::string_view data)
{
	std::string result;

	result += "Error: ";
#if defined(_WIN32)
	constexpr std::size_t buffer_size{256UL};
	char buffer[buffer_size];
	if (strerror_s(buffer, sizeof(buffer), errno) != 0)
	{
		throw std::runtime_error("Can't create message for exception error writing data to file!");
	}

	result += buffer;
#else
	result += std::strerror(errno);
#endif
	result += "; ";

	result += "File: ";  result += filename; result += "; ";
	result += "Data: '"; result += data; 	 result += "; ";

	return result;
}
}  // namespace N_TelegramBotTagging::N_Utilities
