// Copyright [2023] <Volodymyr Dorozhovets>"

#if defined(_WIN32)
#include "framework.hpp"
#endif

#include <fstream>

#include "logger.hpp"
#include "exception/error_writing_data_to_error_log_file.hpp"
#include "utilities.hpp"


namespace N_TelegramBotTagging
{
void Logger::operator()()
{
	const bool &threading_enabled{this->m_thread_pool.IsThreadingEnabled()};

	while(threading_enabled)
	{
		this->LogDataPeriodically();
		this->AppendProgramStatusData(Logger::GenerateDefaultProgramStatusData());
		std::this_thread::sleep_for(std::chrono::seconds(Logger::S_DEFAULT_LOGGING_PERIOD));
	}
}

void Logger::AppendUsersRequestsData(const TgBot::Message::Ptr &message,
									 const std::string_view    request_command)
{
	const std::string user_first_name{message->from->firstName};
	const std::string user_id{std::to_string(message->from->id)};

	std::string request_data{"The '"};
	request_data += std::string(request_command);
	request_data +=	"' command was successfully executed by the user ";
	request_data += user_first_name;
	request_data += " with the following identifier ";
	request_data += user_id;
	request_data += ".\n";

	this->AppendUsersRequestsData(request_data);
}

inline void Logger::LogDataPeriodically()
{
	this->LogProgramStatus();
	this->LogUserRequests ();
	this->LogErrors       ();
}

void Logger::Log(const std::string_view filename, std::string &&data)
{
	std::ofstream file{filename.data(), std::ios::app};
	if (file.is_open())
	{
		std::string output_data{std::move(data)};
		file << output_data;
	}
	else
	{
		Logger::GenerateException(filename, std::move(data));
	}
}

void Logger::GenerateException(const std::string_view filename, std::string &&data)
{
	std::string message
		= N_TelegramBotTagging::N_Utilities::CreateMessageForExceptionErrorWritingDataToFile(filename,
																							 std::string(std::move(data)));

	if(filename == Logger::S_DEFAULT_LOG_FILE_ERRORS)
	{
		throw N_Exception::ErrorWritingDataToErrorLogFile(message);
	}
	else
	{
		throw std::ofstream::failure(message);
	}
}

std::string Logger::GetCurrentTime()
{
	std::chrono::system_clock::time_point current_time_point{std::chrono::system_clock::now()};

	std::time_t current_time_t{std::chrono::system_clock::to_time_t(current_time_point)};

#if defined(_WIN32)
	constexpr std::size_t array_size{26UL};
	char array_current_time[array_size];
	if(ctime_s(array_current_time, sizeof(array_current_time), &current_time_t) != 0)
	{
		throw std::runtime_error("Error: ctime_s() failed.");
	}
	std::string current_time{array_current_time};
#else
	std::string current_time{ctime(&current_time_t)};
#endif

	(void)current_time.erase(std::remove_if(current_time.begin(), current_time.end(),
											[](char symbol)
											{
												return symbol == '\n';
											}), current_time.end());

	return current_time;
}
}  // namespace N_TelegramBotTagging
