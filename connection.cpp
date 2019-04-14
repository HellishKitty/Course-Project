#include "connection.hpp"


int connection::open()
{
	return sqlite3_open(file_name_.c_str(), &data_base_);	
}

int connection::close() const
{
	return sqlite3_close(data_base_);
}

int connection::execute(const std::string& SQLtext)
{
	char* error_message = nullptr;
	open();
	auto response = sqlite3_exec(data_base_, SQLtext.c_str(), default_callback, nullptr, &error_message);
	close();
	if (error_message != nullptr) 
		raise_error(response, error_message);
	okay_ = true;
	return response;
}

int connection::execute(const std::string& SQLtext, void* fetch_here)
{
	char* error_message = nullptr;
	open();
	auto response = sqlite3_exec(data_base_, SQLtext.c_str(), default_callback, fetch_here, &error_message);
	close();
	if (error_message != nullptr)
		raise_error(response, error_message);
	okay_ = true;
	return response;
}

int connection::execute(const std::string& SQLtext, void* fetch_here, callback func)
{
	char* error_message = nullptr;
	open();
	auto response = sqlite3_exec(data_base_, SQLtext.c_str(), default_callback, fetch_here, &error_message);
	close();
	if (error_message != nullptr)
		raise_error(response, error_message);
	okay_ = true;
	return response;
}

void connection::raise_error(const int& code, const std::string& message)
{
	last_error_ = database_exception(code, message);
	okay_ = false;
	throw database_exception(last_error_);
}

std::string connection::get_last_error_message() const
{
	return last_error_.get_error_message();	
}

int connection::get_last_error_code() const
{
	return last_error_.get_error_code();
}

bool connection::was_ok() const
{
	return okay_;	
}

connection::connection(const std::string& file_name) :
						data_base_(nullptr), file_name_(file_name)
{
	okay_ = true;
}

connection::~connection()
{
	data_base_ = nullptr;	
}
