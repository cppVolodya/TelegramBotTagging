// Copyright [2023] <Volodymyr Dorozhovets>"

#ifndef DATABASE_MANAGER_HPP
#define DATABASE_MANAGER_HPP

#include <string>
#include <string_view>
#include <vector>
#include <climits>
#include <iostream>

#include <SQLiteCpp/SQLiteCpp.h>

#include "manager/tables/groups.hpp"
#include "manager/tables/users.hpp"


namespace N_TelegramBotTagging::N_Database
{
class Manager
{
public:
	inline static constexpr std::string_view S_DEFAULT_DATABASE_NAME
		= "database/telegram_bot_tagging.db";
public:
	inline explicit Manager(std::string_view database_name = S_DEFAULT_DATABASE_NAME);

	void CreateUsersTable(int64_t group_id);

	[[nodiscard]] inline static std::string GetTableNameUsersByGroupId(int64_t group_id);

	void AddDataToGroupsTable(N_Tables::Groups groups);

	void AddDataToUsersTable(std::string_view table_name, const N_Tables::Users& users);

	bool CheckIfIdAddedToTable(std::string_view table_name, int64_t id);

	template<typename T>
	inline void UpdateValueInTable(std::string_view table,
								   std::string_view column,
							       T value,
								   std::string_view condition = "");

	void IncrementValueInTableById(std::string_view table_name,
								   std::string_view column,
								   int value,
								   int64_t id);

	void DecrementValueInTableById(std::string_view table_name,
								   std::string_view column,
								   int value,
								   int64_t id);

	template<typename T>
	inline std::vector<T> GetDataFromTableUnderCondition(std::string_view table_name,
														 std::string_view column,
														 std::string_view condition = "");

	SQLite::Statement GetStatementOfDataFromTableUnderCondition(std::string_view table_name,
																std::string_view column,
																std::string_view condition = "");
private:
	std::string m_database_name;

	SQLite::Database m_database;
};

inline Manager::Manager(const std::string_view database_name)
	: m_database_name(database_name),
	  m_database(m_database_name, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE)
{
	const std::string query{"CREATE TABLE IF NOT EXISTS groups(id 				       INTEGER PRIMARY KEY,"
								   							  "number_pending_requests INTEGER DEFAULT 0);"};
	const auto result{this->m_database.exec(query)};

	if (result != 0)
	{
		const std::string error_message{"Database: Failed to create table groups!"};
		throw std::runtime_error(error_message);
	}
}

[[nodiscard]] inline std::string Manager::GetTableNameUsersByGroupId(int64_t group_id)
{
	std::string result{"group_"};
	if(group_id >= 0)
	{
		result += std::to_string(group_id);
	}
	else
	{
		result += "m_";

		std::string group_id_string{std::to_string(group_id)};
		(void)group_id_string.erase(0UL, 1UL);
		result += group_id_string;
	}
	result += "_users";

	return result;
}

template<typename T>
inline void Manager::UpdateValueInTable(const std::string_view table,
								        const std::string_view column,
								        const T value,
								        const std::string_view condition)
{
	std::string query{"UPDATE "};
	query += std::string(table);
	query += " SET ";
	query += std::string(column);
	query += " = ?";

	query += (condition.empty()
		? (";")
		: (" WHERE " + std::string(condition) + ";"));

	SQLite::Statement statement(this->m_database, query);

	statement.bind(1, value);

	(void)statement.exec();
}

template<typename T>
inline std::vector<T> Manager::GetDataFromTableUnderCondition(std::string_view table_name,
															  std::string_view column,
															  std::string_view condition)
{
	SQLite::Statement statement(this->GetStatementOfDataFromTableUnderCondition(table_name,
																				column,
																				condition));

	std::vector<T> result;
	if(statement.executeStep())
	{
		result.reserve(static_cast<std::size_t>(statement.getColumn(0).size()));

		do
		{
			(void)result.emplace_back(statement.getColumn(0));
		} while(statement.executeStep());
	}

	return result;
}

template<>
inline std::vector<std::string> Manager::GetDataFromTableUnderCondition(std::string_view table_name,
															            std::string_view column,
															            std::string_view condition)
{
	SQLite::Statement statement(this->GetStatementOfDataFromTableUnderCondition(table_name,
																				column,
																				condition));

	std::vector<std::string> result;
	if(statement.executeStep())
	{
		result.reserve(static_cast<std::size_t>(statement.getColumn(0).size()));

		do
		{
			(void)result.emplace_back(statement.getColumn(0).getString());
		} while(statement.executeStep());
	}

	return result;
}
}  // namespace N_TelegramBotTagging::N_Database

#endif  // DATABASE_MANAGER_HPP
