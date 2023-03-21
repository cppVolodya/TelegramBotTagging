// Copyright [2023] <Volodymyr Dorozhovets>"

#if defined(_WIN32)
#include "framework.hpp"
#endif

#include "database.hpp"
#include <iostream>


namespace N_TelegramBotTagging::N_Database
{
void Manager::CreateUsersTable(const int64_t group_id)
{
	const std::string table_name = Manager::GetTableNameUsersByGroupId(group_id);

	constexpr std::size_t minimum_size{210UL};
	std::string query;
	query.reserve(minimum_size);
	query += "CREATE TABLE IF NOT EXISTS "; query += table_name;
	query += " (";
	query += "id INTEGER PRIMARY KEY,";
	query += "group_id INTEGER DEFAULT "; query += std::to_string(group_id); query += ",";
	query += "tag TEXT,";
	query += "selected BOOL DEFAULT 1,";
	query += "first_name TEXT,";
	query += "FOREIGN KEY(group_id) REFERENCES groups(id)";
	query += ");";

	const auto result{this->m_database.exec(query)};

	if (result != 1)
	{
		throw std::runtime_error("Database: can't create table " + table_name);
	}
}

void Manager::AddDataToGroupsTable(const N_Tables::Groups groups)
{
	const std::string query{"INSERT INTO groups(id) VALUES (?);"};
	SQLite::Statement statement(this->m_database, query);

	statement.bind(1, groups.m_id);

	const auto result{statement.exec()};

	if (result != 1)
	{
		const std::string error_message{"Database: can't add data to table groups! "};
		throw std::runtime_error(error_message);
	}
}

void Manager::AddDataToUsersTable(const std::string_view table_name, const N_Tables::Users &users)
{
	std::string query{"INSERT INTO "};
	query += std::string(table_name);
	query += " (id, tag, first_name) VALUES (?, ?, ?);";

	SQLite::Statement statement(this->m_database, query);

	statement.bind(1, users.GetId());
	statement.bind(2, users.GetTag());
	statement.bind(3, users.GetFirstName());

	const auto result{statement.exec()};

	if (result != 1)
	{
		throw std::runtime_error("Database: can't add data to table " + std::string(table_name));
	}
}

bool Manager::CheckIfIdAddedToTable(const std::string_view table_name, const int64_t id)
{
	std::string query{"SELECT id FROM "};
	query += std::string(table_name);
	query += " WHERE id = ?;";

	SQLite::Statement statement(this->m_database, query);

	statement.bind(1, id);

	const auto step_success{statement.executeStep()};
	bool result{false};
	if (step_success)
	{
		result = (statement.getColumn(0).getInt64() == id);
	}

	return result;
}

void Manager::IncrementValueInTableById(const std::string_view table_name,
										const std::string_view column,
										const int value,
										const int64_t id)
{
	std::string query{"UPDATE "}; query += std::string(table_name);
	query += " SET ";
	query += std::string(column);
	query += " = ";
	query += std::string(column);
	query += " + ? ";
	query += " WHERE id = ?;";

	SQLite::Statement statement(this->m_database, query);

	statement.bind(1, value);
	statement.bind(2, id   );

	(void)statement.exec();
}

void Manager::DecrementValueInTableById(const std::string_view table_name,
										const std::string_view column,
										const int value,
										const int64_t id)
{
	this->IncrementValueInTableById(table_name, column, -value, id);
}

SQLite::Statement Manager::GetStatementOfDataFromTableUnderCondition(std::string_view table_name,
																	 std::string_view column,
																	 std::string_view condition)
{
	std::string query{"SELECT "};
	query += std::string(column    );
	query += " FROM ";
	query += std::string(table_name);

	query += (condition.empty())
		? (";")
		: (" WHERE " + std::string(condition) + ";");

	SQLite::Statement statement(this->m_database, query);

	return statement;
}
}  // namespace N_TelegramBotTagging::N_Database
