#include "logging.hpp"
#include "connection.hpp"
#include <iostream>

user* logging_options::current_callback_data_ = nullptr;

user* logging_options::sign_in()
{
	connection conn("Taxi.sqlite3");
	auto user_logging_data = ask_logging_data();
	auto SQLtext = form_sign_in(user_logging_data);
	conn.execute(SQLtext, nullptr, sign_in_callback);
	return current_callback_data_;
}

user* logging_options::sign_up()
{
	connection conn("Taxi.sqlite3");
	auto role = register_as();
	auto user_credentials = ask_credentials();
	auto user_logging_data = ask_logging_data();	
	auto SQLtext = form_sign_up(user_logging_data, user_credentials, role);
	conn.execute(SQLtext, nullptr);
	return new user(user_logging_data, user_credentials, role);
}

int logging_options::register_as()
{
	std::string reg = "null";
	while (register_roles.count(reg) == 0)
	{
		std::cout << "1) Зарегистрироваться как водитель || 2) Зарегистрироваться как пассажир" << std::endl;
		std::cout << "Ввод> ";
		std::getline(std::cin, reg, '\n');
	}
	return register_roles[reg];
}

credentials logging_options::ask_credentials() const
{
	credentials credits;
	std::cout << "Введите ваше имя: ";
	std::getline(std::cin, credits.name, '\n');
	std::cout << "Введите вашу фамилию: ";
	std::getline(std::cin, credits.surname, '\n');
	return credits;
}

logging_data logging_options::ask_logging_data() const
{
	logging_data data;
	std::cout << "Введите логин: ";
	std::getline(std::cin, data.login, '\n');
	std::cout << "Введите пароль: ";
	std::getline(std::cin, data.password, '\n');
	return data;
}

std::string logging_options::form_sign_in(const logging_data& data)
{
	return "SELECT * FROM users WHERE login = '" + data.login + "' and password = '" + data.password + "'";
}

std::string logging_options::form_sign_up(const logging_data& data, const credentials& credits, const int& role) const
{
	return "INSERT INTO users (login, password, name, surname, role) " \
		    "VALUES ('" +  data.login + "', '" + data.password + "', '" + credits.name + "', '" + credits.surname + "', " + std::to_string(role) + ")";

}

int logging_options::sign_in_callback(void* user_found, int count, char** value, char** column_name)
{
	logging_data data;
	credentials credits;

	data.login = value[0];
	data.password = value[1];
	credits.name = value[2];
	credits.surname = value[3];
	auto role = atoi(value[4]);

	current_callback_data_ = new user(data, credits, role);
	return 0;
}

logging_options::logging_options()
{
	current_callback_data_ = nullptr;	
}

