#pragma once
#include "user.hpp"

typedef class admin_options final
{
public:
	void add_user();
	void delete_user();
	void update_user(); 
	void select_users();
	void write_request();
	void load_request();

private:
	credentials ask_credentials();
	logging_data ask_logging_data();
	int ask_role();

	int ask_how_select();
	std::string get_select_SQLtext();

	int ask_what_update();
	std::string ask_value(const std::string& column);
	std::string get_update_SQLtext();
	bool ask_to_continue();
	std::string ask_login();

	bool ask_to_continue_unsafe();
	std::string load_from_file();
	std::string ask_file_name();

	std::string form_insert_user(const logging_data& data, const credentials& credits, const int& role);
	std::string form_print_users(const credentials& credits, const int& role);
	std::string form_print_users(const credentials& credits);
	std::string form_print_users(const int& role);
	std::string form_print_users();
	std::string form_delete(const std::string& login);
	std::string form_update(const std::string& login, const std::string& column, const std::string& value);

	static int select_callback(void *not_used, int argc, char **argv, char **columns);

public:
	admin_options(user* log_in);
	~admin_options() = default;
	
	std::map<std::string, int> extended_role_map  = {

	{"0", ADMIN},
	{"admin", ADMIN},
	{"1", DRIVER},
	{"driver", DRIVER},
	{"2", PASSENGER},
	{"passenger", PASSENGER}
};

	std::map<std::string, bool> bool_dictionary = {

	{"1", true}, {"Y", true}, {"y", true}, {"yes", true}, {"Yes", true},
	{"0", false}, {"N", false}, {"n", false}, {"No", false}, {"Not", false}, {"not", false}
};
} admin;
