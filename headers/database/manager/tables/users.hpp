// Copyright [2023] <Volodymyr Dorozhovets>"

#ifndef DATABASE_TABLES_USERS_HPP
#define DATABASE_TABLES_USERS_HPP

#include <string>
#include <string_view>


namespace N_TelegramBotTagging::N_Database::N_Tables
{
class Users
{
public:
	inline explicit Users(int64_t 		   id 	      = 0,
						  std::string_view tag 		  = "",
						  std::string_view first_name = "") noexcept;

	[[nodiscard]] inline int64_t 	 GetId() 		const noexcept;
	[[nodiscard]] inline std::string GetTag() 		const noexcept;
	[[nodiscard]] inline std::string GetFirstName() const noexcept;

private:
	int64_t 	m_id;
	std::string m_tag;
	std::string m_first_name;
};

inline Users::Users(const int64_t 		   id,
					const std::string_view tag,
					const std::string_view first_name) noexcept
	: m_id		  (id		 ),
	  m_tag		  (tag       ),
	  m_first_name(first_name)
{
}

[[nodiscard]] inline int64_t Users::GetId() const noexcept
{
	return this->m_id;
}

[[nodiscard]] inline std::string Users::GetTag() const noexcept
{
	return this->m_tag;
}

[[nodiscard]] inline std::string Users::GetFirstName() const noexcept
{
	return this->m_first_name;
}
}  // namespace N_TelegramBotTagging::N_Database::N_Tables

#endif  // DATABASE_TABLES_USERS_HPP
