// Copyright [2023] <Volodymyr Dorozhovets>"

#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string_view>

#include <tgbot/tgbot.h>

#include "thread_pool.hpp"


namespace N_TelegramBotTagging
{
class Logger
{
public:
	inline static constexpr std::string_view S_DEFAULT_LOG_FILE_PROGRAM_STATUS{"log_files/program_status.log"};
	inline static constexpr std::string_view S_DEFAULT_LOG_FILE_USER_REQUESTS {"log_files/user_requests.log" };
	inline static constexpr std::string_view S_DEFAULT_LOG_FILE_ERRORS		  {"log_files/errors.log"		 };
	inline static constexpr std::string_view S_DEFAULT_PROGRAM_STATUS_DATA    {"The program works!"		     };
public:
	inline explicit Logger(const ThreadPool &thread_pool = ThreadPool());

	void operator()();

	inline void LogProgramStatus();
	inline void LogUserRequests ();
	inline void LogErrors	    ();

	inline void LogErrors(std::string_view data);

	inline void AppendProgramStatusData(std::string_view data);

	inline void AppendUsersRequestsData(std::string_view data);

	void AppendUsersRequestsData(const TgBot::Message::Ptr &message,
								 std::string_view           request_command);

	inline void AppendErrorsData(std::string_view data);
private:
	inline static constexpr unsigned int S_DEFAULT_PROGRAM_STATUS_DATA_SIZE = 100U;
    inline static constexpr unsigned int S_DEFAULT_USER_REQUEST_DATA_SIZE   = 1000U;
	inline static constexpr unsigned int S_DEFAULT_ERRORS_DATA_SIZE         = 200U;

	inline static constexpr std::chrono::seconds S_DEFAULT_LOGGING_PERIOD{10};
private:
	const ThreadPool &m_thread_pool;

	std::string m_program_status_data;
	std::string m_users_requests_data;
	std::string m_errors_data;

	inline static std::mutex m_mutex_program_status_data;
	inline static std::mutex m_mutex_users_requests_data;
	inline static std::mutex m_mutex_errors_data;
private:
	inline void LogDataPeriodically();

	static void Log(std::string_view filename, std::string &&data);

	static void GenerateException(std::string_view filename, std::string &&data);

	inline static std::string GenerateDefaultProgramStatusData();

	static std::string GetCurrentTime();
};

inline Logger::Logger(const ThreadPool &thread_pool)
	: m_thread_pool(thread_pool)
{
	this->m_program_status_data.reserve(Logger::S_DEFAULT_PROGRAM_STATUS_DATA_SIZE);
	this->m_program_status_data = Logger::GenerateDefaultProgramStatusData();

	this->m_users_requests_data.reserve(Logger::S_DEFAULT_USER_REQUEST_DATA_SIZE  );
	this->m_errors_data        .reserve(Logger::S_DEFAULT_ERRORS_DATA_SIZE		  );
}

inline void Logger::LogProgramStatus()
{
	const std::lock_guard<std::mutex> lock{Logger::m_mutex_program_status_data};
	if(not this->m_program_status_data.empty())
	{
		Logger::Log(Logger::S_DEFAULT_LOG_FILE_PROGRAM_STATUS, std::move(this->m_program_status_data));
	}
}

inline void Logger::LogUserRequests()
{
	const std::lock_guard<std::mutex> lock{Logger::m_mutex_users_requests_data};
	if(not this->m_users_requests_data.empty())
	{
		Logger::Log(Logger::S_DEFAULT_LOG_FILE_USER_REQUESTS, std::move(this->m_users_requests_data));
	}
}

inline void Logger::LogErrors()
{
	const std::lock_guard<std::mutex> lock{Logger::m_mutex_errors_data};
	if(not this->m_errors_data.empty())
	{
		Logger::Log(Logger::S_DEFAULT_LOG_FILE_ERRORS, std::move(this->m_errors_data));
	}
}

inline void Logger::LogErrors(const std::string_view data)
{
	this->AppendErrorsData(data);
	this->LogErrors();
}

inline void Logger::AppendProgramStatusData(const std::string_view data)
{
	const std::lock_guard<std::mutex> lock{Logger::m_mutex_program_status_data};
	(void)this->m_program_status_data.append(data);
}

inline void Logger::AppendUsersRequestsData(const std::string_view data)
{
	const std::lock_guard<std::mutex> lock{Logger::m_mutex_users_requests_data};
	(void)this->m_users_requests_data.append(data);
}

inline void Logger::AppendErrorsData(const std::string_view data)
{
	const std::lock_guard<std::mutex> lock{Logger::m_mutex_errors_data};
	(void)this->m_errors_data.append(data);
}

inline std::string Logger::GenerateDefaultProgramStatusData()
{
	std::string data;
	data += "["; data += Logger::GetCurrentTime(); data += "] ";
	data += std::string(Logger::S_DEFAULT_PROGRAM_STATUS_DATA);
	data += "\n";

	return data;
}
}  // namespace N_TelegramBotTagging

#endif  // LOGGER_HPP
