#pragma once
#include "sqlite3.h"
#include <string>
#include "database_exception.hpp"

using SQLite = sqlite3;
using callback = sqlite3_callback;

class connection final
{
	SQLite* data_base_;
	std::string file_name_;
	database_exception last_error_;
	bool okay_;

	static int default_callback(void *not_used, int argc, char **argv, char **columns);

	void raise_error(const int& code, const std::string& message);

public:

	int execute(const std::string& SQLtext);
	int execute(const std::string& SQLtext, void* fetch_here);
	int execute(const std::string& SQLtext, void* fetch_here, callback func);
	int open();
	int close() const;

	bool was_ok() const;
	int get_last_error_code() const;
	std::string get_last_error_message() const;

	connection(const std::string& file_name);
	~connection();
};
