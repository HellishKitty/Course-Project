#include "logging.hpp"
#include <iostream>

user* logging::current_callback_data_ = nullptr;

user* logging::sign_in()
{
	connection conn("Taxi.sqlite3");
	auto user_logging_data = ask_logging_data();
	auto SQLtext = form_sign_in(user_logging_data);
	try_execute(conn, SQLtext, sign_in_callback);
	return current_callback_data_;
}

user* logging::sign_up()
{
	connection conn("Taxi.sqlite3");
	auto role = register_as();
	auto user_credentials = ask_credentials();
	auto user_logging_data = ask_logging_data();	
	auto SQLtext = form_sign_up(user_logging_data, user_credentials, role);
	if (try_execute(conn, SQLtext, nullptr) == 0)
		return new user(user_logging_data, user_credentials, role);
	return nullptr;
}

int logging::register_as()
{
	std::string reg = "null";
	while (register_roles.count(reg) == 0)
	{
		std::cout << "1) register as driver || 2) register as passenger" << std::endl;
		std::cout << "Input> ";
		std::getline(std::cin, reg, '\n');
	}
	return register_roles[reg];
}

credentials logging::ask_credentials()
{
	credentials credits;
	std::cout << "Enter your name: ";
	std::getline(std::cin, credits.name, '\n');
	std::cout << "Enter your surname: ";
	std::getline(std::cin, credits.surname, '\n');
	return credits;
}

logging_data logging::ask_logging_data()
{
	logging_data data;
	std::cout << "Enter your login: ";
	std::getline(std::cin, data.login, '\n');
	std::cout << "Enter your password: ";
	std::getline(std::cin, data.password, '\n');
	return data;
}

std::string logging::form_sign_in(const logging_data& data)
{
	return "SELECT * FROM users WHERE login = '" + data.login + "' and password = '" + data.password + "'";
}

std::string logging::form_sign_up(const logging_data& data, const credentials& credits, const int& role)
{
	return "INSERT INTO users (login, password, name, surname, role) " \
		    "VALUES ('" +  data.login + "', '" + data.password + "', '" + credits.name + "', '" + credits.surname + "', " + std::to_string(role) + ")";

}

int logging::try_execute(connection& conn, const std::string& SQLtext, callback func)
{
	try	{
		conn.execute(SQLtext, nullptr, func);
		return 0;
	} catch (database_exception& exception) {
		// TODO: do smth with error code
	}
	return 1;
}

int logging::sign_in_callback(void* user_found, int count, char** value, char** column_name)
{
	logging_data data;
	credentials credits;
	int role;

	data.login = value[0];
	data.password = value[1];
	credits.name = value[2];
	credits.surname = value[3];
	role = atoi(value[4]);

	current_callback_data_ = new user(data, credits, role);
	return 0;
}

std::map<std::string, int > logging::register_roles = {
	{"1", DRIVER},
	{"driver", DRIVER},
	{"2", PASSENGER},
	{"passenger", PASSENGER}
};
