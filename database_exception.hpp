#pragma once
#include <exception>
#include <string>

class database_exception :  std::exception
{
	int code_;
	std::string message_;
public:
	int get_error_code() const;
	std::string get_error_message() const;
	char const* what() const override;

	database_exception() noexcept;
	database_exception(const int& code, const std::string& message) noexcept;
	database_exception(const database_exception& orig) noexcept { };
	~database_exception() = default;
};
