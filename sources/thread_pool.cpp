// Copyright [2023] <Volodymyr Dorozhovets>"

#if defined(_WIN32)
#include "framework.hpp"
#endif

#include <thread>
#include <string>

#include "thread_pool.hpp"
#include "exception/thread_timeout.hpp"


namespace N_TelegramBotTagging
{
void ThreadPool::Pause()
{
	if(this->m_threading_enabled)
	{
		this->m_threading_enabled = false;
		this->m_bs_thread_pool.pause();

		const bool all_tasks_finished
			{m_bs_thread_pool.wait_for_tasks_duration(std::chrono::seconds(ThreadPool::S_DEFAULT_THREADS_WAIT_TIME_SECONDS))};
		if(not all_tasks_finished)
		{
			constexpr std::size_t minimum_size{130U};
			std::string error_message;
			error_message.reserve(minimum_size);
			error_message += "An error occurred: Threads were not completed successfully ";
			error_message += "tasks queued: ";  error_message += std::to_string(this->m_bs_thread_pool.get_tasks_queued ()); error_message += "; ";
			error_message += "tasks running: "; error_message += std::to_string(this->m_bs_thread_pool.get_tasks_running()); error_message += "; ";
			error_message += "tasks total: ";   error_message += std::to_string(this->m_bs_thread_pool.get_tasks_total  ()); error_message += "; ";
			error_message += "thread count: ";  error_message += std::to_string(this->m_bs_thread_pool.get_thread_count ()); error_message += "; ";

			throw N_Exception::ThreadTimeout(error_message);
		}
	}
}

unsigned int ThreadPool::CalculateNumberOfThreads() noexcept
{
	const unsigned int number_hardware_threads{std::thread::hardware_concurrency()};
	constexpr unsigned int min_number_threads{2U};

	unsigned int result = (number_hardware_threads < min_number_threads)
		? min_number_threads      + 1U
		: number_hardware_threads + 1U;

	return result;
}
}  // namespace N_TelegramBotTagging
