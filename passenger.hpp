#pragma once
#include "user.hpp"
#include "order.hpp"


typedef class passenger_options final
{
	static int max_ID_;
	static std::vector<user> callback_drivers_;
public:
	static std::map<std::string, bool> commit_options;
	static void order_taxi(const std::string& login);
	static void edit_credentials(const std::string& login);
	static void change_password(const std::string& login);	
private:
	static order_info ask_order_info();
	static user select_driver();
	static void print_drivers_found();
	static user pick_driver();
	static int generate_cost();
	static int generate_id();
	static bool ask_commit(const order_info& info, const user& driver);	
	static void print_order_info(const order_info& info, const user& driver);
	static void insert(const std::string& SQLtext);

	static credentials ask_new_credentials();
	static void update(const std::string& SQLtext);
	static std::string ask_new_password();

	static std::string form_update_credits(const credentials& credits, const std::string& login);
	static std::string form_update_password(const std::string& password ,const std::string& login);
	static std::string form_max_id_req();
	static std::string form_select_drivers();
	static std::string form_commit(const order_info& info, const std::string& driver, const std::string& passenger);
	static int max_id_callback(void* not_used, int count, char** value, char** column_name);
	static int select_drivers_callback(void* not_used, int count, char** value, char** column_name);
} passenger;
