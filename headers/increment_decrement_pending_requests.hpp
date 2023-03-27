// Copyright [2023] <Volodymyr Dorozhovets>"

#ifndef INCREMENT_DECREMENT_PENDING_REQUESTS_HPP
#define INCREMENT_DECREMENT_PENDING_REQUESTS_HPP

#include <string>

#include "manager/database.hpp"


namespace N_TelegramBotTagging
{
class IncrementDecrementPendingRequests final
{
public:
	inline explicit IncrementDecrementPendingRequests(int64_t group_id,
													  N_Database::Manager *database_manager);

#pragma region RuleOfZero [r_functions]
	inline IncrementDecrementPendingRequests(const IncrementDecrementPendingRequests &) = delete;
	inline IncrementDecrementPendingRequests(IncrementDecrementPendingRequests      &&) = delete;

	inline IncrementDecrementPendingRequests& operator=(const IncrementDecrementPendingRequests &) = delete;
	inline IncrementDecrementPendingRequests& operator=(IncrementDecrementPendingRequests      &&) = delete;

	inline ~IncrementDecrementPendingRequests();
#pragma endregion RuleOfZero [r_functions]

	void Increment();
	void Decrement();
private:
	inline static constexpr std::string_view S_TABLE{"groups"};

	inline static constexpr int S_VALUE{1};

	inline static constexpr std::string_view S_COLUMN{"number_pending_requests"};
private:
	int64_t m_group_id;

	bool m_enable_destroy;

	N_Database::Manager *m_database_manager;
};

inline IncrementDecrementPendingRequests::IncrementDecrementPendingRequests
	(const int64_t group_id, N_Database::Manager *database_manager)
	: m_group_id(group_id),
	  m_enable_destroy(false),
	  m_database_manager(database_manager)
{
	this->Increment();
}

inline IncrementDecrementPendingRequests::~IncrementDecrementPendingRequests()
{
	if(this->m_enable_destroy)
	{
		this->Decrement();
	}
}

inline void IncrementDecrementPendingRequests::Increment()
{
	this->m_database_manager->IncrementValueInTableById(S_TABLE,
														S_COLUMN,
														S_VALUE,
														this->m_group_id);
}

inline void IncrementDecrementPendingRequests::Decrement()
{
	this->m_database_manager->DecrementValueInTableById(S_TABLE,
														S_COLUMN,
														S_VALUE,
														this->m_group_id);
}
}  // namespace N_TelegramBotTagging

#endif  // INCREMENT_DECREMENT_PENDING_REQUESTS_HPP
