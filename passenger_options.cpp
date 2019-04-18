#include "passenger_options.hpp"
#include "connection.hpp"
#include "options_exception.hpp"
#include <iostream>
#define RAND_MAX 10

int passenger_options::max_ID_ = 0;
std::vector<user> passenger_options::callback_drivers_;

void passenger_options::order_taxi()
{
	auto order = ask_order_info();
	auto driver = select_driver();
	order.cost = generate_id();
	order.order_id = generate_id();	
	if (ask_commit(order, driver))
		order.status = COMPLETED;
	else
		order.status = DECLINED;
	auto SQLtext = form_commit(order, driver.get_credential().name, current_user_.get_login());
	insert(SQLtext);
	callback_drivers_.clear();
}

order_info passenger_options::ask_order_info()
{
	order_info order;
	std::cout << "Введите ваш адрес: ";
	std::getline(std::cin, order.from_address, '\n');
	std::cout << "введите адрес прибытия: ";
	std::getline(std::cin, order.to_address, '\n');
	return order;
}

user passenger_options::select_driver()
{
	connection conn("Taxi.sqlite3");
	conn.execute(form_select_drivers(), nullptr, select_drivers_callback);
	print_drivers_found();
	auto driver = pick_driver();
	return driver;
}

bool passenger_options::ask_commit(const order_info& info, const user& driver)
{
	std::string commit = "null";
	print_order_info(info, driver);
	while (commit_options.count(commit) == 0) {
		std::cout << "1) Подтвердить поездку || 0) Отменить поездку\nInput> ";
		std::getline(std::cin, commit, '\n');
	}
	return commit_options[commit];
}

void passenger_options::print_orders()
{
	connection conn("Taxi.sqlite3");
	conn.execute("SELECT * FROM orders WHERE plogin = '" + current_user_.get_login() + "'", nullptr, select_orders_callback);
}

void passenger_options::insert(const std::string& SQLtext)
{
	connection conn("Taxi.sqlite3");
	conn.execute(SQLtext);
}

void passenger_options::print_order_info(const order_info& info, const user& driver)
{
	std::cout << "Из " << info.from_address << " к " << info.to_address << std::endl;
	std::cout << "Цена: " << info.cost << ", водитель " << driver.get_credential() << std::endl;
}

void passenger_options::print_drivers_found()
{
	for (auto i = 0; i != callback_drivers_.size(); ++i)
		std::cout << i + 1 << ") " << callback_drivers_.at(i).get_credential() << std::endl;
}
user passenger_options::pick_driver()
{
	std::string pick;
	while (true)
	{
		try {
			std::cout << "Выберите водителя: ";
			std::getline(std::cin, pick, '\n');
			return callback_drivers_.at(std::stoi(pick) - 1);
		} catch (std::invalid_argument& e)	{
			std::cout << "Ошибка ввода! Попробуйте ещё раз." << std::endl;
		} catch (std::out_of_range& e) {
			std::cout << "Выбран неправильный номер! Попроубуйте ещё раз." << std::endl;
		}
	}	
}

int passenger_options::generate_cost()
{
	return 5 + std::rand();
}

int passenger_options::generate_id()
{
	max_ID_ = -1;
	connection conn("Taxi.sqlite3");
	conn.execute(form_max_id_req(), nullptr, max_id_callback);
	if (max_ID_ == -1)
		throw bad_order_id();
	return max_ID_ + 1;
}

std::string passenger_options::form_max_id_req()
{
	return "SELECT MAX(id) FROM orders";	
}

std::string passenger_options::form_select_drivers()
{
	return "SELECT name, surname, login, password FROM users WHERE role = 1";
}

std::string passenger_options::form_commit(const order_info& info, const std::string& driver, const std::string& passenger)
{
	return "INSERT INTO orders VALUES (" + std::to_string(info.order_id) + ", '" + driver + "', '" + passenger + "', '"\
			+ info.from_address + "', '" + info.to_address + "', " + std::to_string(info.status) + ")";
}

std::string passenger_options::form_select_orders(const std::string& login)
{
	return "SELECT * FROM orders WHERE login = '" + login + "'";
}

int passenger_options::max_id_callback(void* not_used, int count, char** value, char** column_name)
{
	max_ID_ = atoi(value[0]);
	return 0;
}

int passenger_options::select_drivers_callback(void* not_used, int count, char** value, char** column_name)
{
	credentials driver_credits;
	driver_credits.name = value[0];
	driver_credits.surname = value[1];
	logging_data data;
	data.login = value[2];
	data.password = "";
	callback_drivers_.emplace_back(data, driver_credits, DRIVER);
	return 0;
}

int passenger_options::select_orders_callback(void* not_used, int count, char** value, char** column_name)
{
	std::cout << "-------------------------" << std::endl;
    for (auto i = 0; i < count; i++) {    
    	std::cout << column_name[i] << ": " << value[i] << std::endl;
    }
	std::cout << "-------------------------" << std::endl;
    return 0; 	
}

passenger_options::passenger_options(user* current) : user_options(current)
{
	
}
