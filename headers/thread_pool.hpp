// Copyright [2023] <Volodymyr Dorozhovets>"

#ifndef THREAD_POOL_HPP
#define THREAD_POOL_HPP

#include <list>
#include <future>

#include <BS_thread_pool.hpp>


namespace N_TelegramBotTagging
{
class ThreadPool
{
public:
	inline ThreadPool();

	template<typename T, typename ... Arguments>
	inline void PushTask(T* task, const Arguments& ... arguments);

	void Pause();

	[[nodiscard]] inline const bool& IsThreadingEnabled() const noexcept;

	[[nodiscard]] inline std::list<std::future<void>>& GetThreadsResults() noexcept;
private:
	static inline constexpr int S_DEFAULT_THREADS_WAIT_TIME_SECONDS{15};
private:
	BS::thread_pool m_bs_thread_pool;

	std::list<std::future<void>> m_threads_results;

	bool m_threading_enabled;
private:
	static unsigned int CalculateNumberOfThreads() noexcept;
};

inline ThreadPool::ThreadPool()
	: m_bs_thread_pool(CalculateNumberOfThreads()),
	  m_threading_enabled(true)
{
}

template<typename T, typename ... Arguments>
inline void ThreadPool::PushTask(T* task, const Arguments& ... arguments)
{
	if(this->m_threading_enabled)
	{
		this->m_threads_results.emplace_back(m_bs_thread_pool.submit(&T::operator(), task, arguments...));
	}
}

[[nodiscard]] inline const bool& ThreadPool::IsThreadingEnabled() const noexcept
{
	return this->m_threading_enabled;
}

[[nodiscard]] inline std::list<std::future<void>>& ThreadPool::GetThreadsResults() noexcept
{
	return this->m_threads_results;
}
}  // namespace N_TelegramBotTagging

#endif  // THREAD_POOL_HPP
