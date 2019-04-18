#pragma once
#include "logging.hpp"


class program
{
	logging_options* logging_options_;
public:
	int main();
	void init_db_if_not_exists(const std::string& file_name);
private:
	char ask_logging_option() const;
	user* try_prefrorm_option(char option) const;
	void start_UI(user* current);
	std::string form_init_users();
	std::string form_init_orders();
public:
	program();
	~program();
};
