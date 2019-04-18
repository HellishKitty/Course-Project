#pragma once
#include "user_options.hpp"
#include "order.hpp"


typedef class passenger_options final : public user_options
{
	static int max_ID_;
	static std::vector<user> callback_drivers_;
public:
	void order_taxi();
	void print_orders();
	std::function<void()> order_taxi_f = std::bind(&passenger_options::order_taxi, this);
	std::function<void()> print_orders_f = std::bind(&passenger_options::print_orders, this);
private:
	order_info ask_order_info();
	user select_driver();
	void print_drivers_found();
	user pick_driver();
	int generate_cost();
	int generate_id();
	bool ask_commit(const order_info& info, const user& driver);	
	void print_order_info(const order_info& info, const user& driver);
	void insert(const std::string& SQLtext);

	std::string form_max_id_req();
	std::string form_select_drivers();
	std::string form_commit(const order_info& info, const std::string& driver, const std::string& passenger);
	std::string form_select_orders(const std::string& login);
	static int max_id_callback(void* not_used, int count, char** value, char** column_name);
	static int select_drivers_callback(void* not_used, int count, char** value, char** column_name);
	static int select_orders_callback(void* not_used, int count, char** value, char** column_name);

public:
	passenger_options(user* current);
	~passenger_options() = default;

	std::map<std::string, bool> commit_options = {

	{"1", true},
	{"y", true},	
	{"yes", true},
	{"Yes", true},
	{"commit", true},
	{"Commit", true},
	{"0", false},
	{"n", false},
	{"N", false},
	{"no", false},
	{"No", false}
};

} passenger;
