#pragma once
#include "user.hpp"
#include <functional>

typedef class admin_options final
{
	user current_;
public:
	void select_users();
	void add_user();
	void update_user();
	void delete_user();
	void write_request();
	void load_request();
	std::function<void()> select_users_f = std::bind(&admin_options::select_users, this);
	std::function<void()> add_user_f  = std::bind(&admin_options::add_user, this);
	std::function<void()> update_user_f = std::bind(&admin_options::update_user, this);
	std::function<void()> del_user_f = std::bind(&admin_options::delete_user, this);
	std::function<void()> write_request_f = std::bind(&admin_options::write_request, this);
	std::function<void()> load_request_f = std::bind(&admin_options::load_request, this);

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
	static int select_callback(void* not_used, int argc, char** argv, char** columns);
public:
	admin_options(user* current);
	~admin_options() = default;
private:
	void bind_functions();
public:
	std::map<std::string, int> extended_role_map = {

		{"0", ADMIN},
		{"администратор", ADMIN},
		{"1", DRIVER},
		{"водитель", DRIVER},
		{"2", PASSENGER},
		{"пассажир", PASSENGER}
	};

	std::map<std::string, bool> bool_dictionary = {

		{"1", true}, {"Да", true}, {"да", true}, {"Подтвердить", true}, {"подтвердить", true},
		{"0", false}, {"Нет", false}, {"нет", false}, {"Отменить", false}, {"отменить", false}
	};
} admin;
