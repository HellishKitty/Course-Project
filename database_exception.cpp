#include "database_exception.hpp"

char const* database_exception::what() const
{
	auto what = "Error " + std::to_string(code_) + " occured: " + message_;
	return what.c_str();
}

int database_exception::get_error_code() const
{
	return code_;
}

std::string database_exception::get_error_message() const
{
	return message_;
}

database_exception::database_exception() noexcept
{
	code_ = 0;
	message_ = "NULL";
}

database_exception::database_exception(const int& code, const std::string& message) noexcept :
										code_(code), message_(message) { }
