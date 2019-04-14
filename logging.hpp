#pragma once
#include "user.hpp"
#include "connection.hpp"



class logging final
{
public:	
	static std::map<std::string, int> register_roles;

	static user* sign_in();
	static user* sign_up();
private:
	static int register_as();
	static credentials ask_credentials();
	static logging_data ask_logging_data();
	static std::string form_sign_in(const logging_data& data);
	static std::string form_sign_up(const logging_data& data, const credentials& credits, const int& role);
	static int try_execute(connection& conn, const std::string& SQLtext, callback func);

	static user* current_callback_data_;
	static int sign_in_callback(void* user_found, int count, char **value, char **column_name);
};
