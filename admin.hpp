#pragma once
#include "user.hpp"

typedef class admin_options final
{
public:
	static void add_user();
	static void delete_user();
	static void update_user(); 
	static void select_users();
	static void write_request();
	static void load_request();

	static std::map<std::string, int> extended_role_map;
	static std::map<std::string, bool> bool_dictionary;

private:
	static credentials ask_credentials();
	static logging_data ask_logging_data();
	static int ask_role();

	static int ask_how_select();
	static std::string get_select_SQLtext();

	static int ask_what_update();
	static std::string ask_value(const std::string& column);
	static std::string get_update_SQLtext();
	static bool ask_to_continue();
	static std::string ask_login();

	static bool ask_to_continue_unsafe();
	static std::string load_from_file();
	static std::string ask_file_name();

	static std::string form_insert_user(const logging_data& data, const credentials& credits, const int& role);
	static std::string form_print_users(const credentials& credits, const int& role);
	static std::string form_print_users(const credentials& credits);
	static std::string form_print_users(const int& role);
	static std::string form_print_users();
	static std::string form_delete(const std::string& login);
	static std::string form_update(const std::string& login, const std::string& column, const std::string& value);

	static int select_callback(void *not_used, int argc, char **argv, char **columns);
} admin;
