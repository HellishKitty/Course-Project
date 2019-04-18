#include "admin.hpp"
#include "connection.hpp"
#include <iostream>
#include <fstream>
#include "options_exception.hpp"


void admin_options::add_user()
{
	auto SQLtext = form_insert_user(ask_logging_data(), ask_credentials(), ask_role());
	connection conn("Taxi.sqlite3");
	conn.execute(SQLtext);
}

credentials admin_options::ask_credentials()
{
	credentials credits;
	std::cout << "Имя: ";
	std::getline(std::cin, credits.name, '\n');
	std::cout << "Фамилия: ";
	std::getline(std::cin, credits.surname, '\n');
	return credits;
}

logging_data admin_options::ask_logging_data()
{
	logging_data data;
	std::cout << "Логин: ";
	std::getline(std::cin, data.login, '\n');
	std::cout << "пароль: ";
	std::getline(std::cin, data.password, '\n');
	return data;
}

int admin_options::ask_role()
{
	std::string role = "null";
	while (extended_role_map.count(role) == 0)
	{
		std::cout << "Введите роль" << std::endl;
		std::cout << "0) администратор || 1) Водитель || 2) Пассажир" << std::endl;
		std::cout << "Ввод> ";
		std::getline(std::cin, role, '\n');
	}
	return extended_role_map[role];
}

void admin_options::select_users()
{
	auto SQLtext = get_select_SQLtext();
	connection conn("Taxi.sqlite3");
	conn.execute(SQLtext, nullptr, select_callback);
}

std::string admin_options::get_select_SQLtext()
{
	std::string SQLtext;
	switch (ask_how_select())
	{
	case 1:
		SQLtext = form_print_users(ask_credentials(), ask_role());
		break;
	case 2:
		SQLtext = form_print_users(ask_credentials());
		break;
	case 3:
		SQLtext = form_print_users(ask_role());
		break;
	case 0:
		SQLtext = form_print_users();
		break;
	default:
		SQLtext = form_print_users();
		break;
	}
	return SQLtext;
}

int admin_options::ask_how_select()
{
	auto select_by = -1;
	while (select_by == -1)
	{
		std::string tmp;
		std::cout << "1) Отбирать по личным данным и роли" << std::endl;
		std::cout << "2) Отбирать по личным данным" << std::endl;
		std::cout << "3) Отбирать по роли" << std::endl;
		std::cout << "0) Выбрать всех" << std::endl;
		std::cout << "Ввод> ";
		std::getline(std::cin, tmp, '\n');
		try	{
			select_by = std::stoi(tmp);
		}
		catch (std::invalid_argument& e) {
			std::cout << "Ошибка ввода! Попробуйте ещё раз.";
		}
	}
	return select_by;	
}

void admin_options::delete_user()
{
	if (! ask_to_continue())
		return;

	auto SQLtext = form_delete(ask_login());
	connection conn("Taxi.sqlite3");
	conn.execute(SQLtext);
}

bool admin_options::ask_to_continue()
{
	std::string continue_ = "null";
	std::cout << "Осторожно! Эта операция не может быть отменена" << std::endl;
	while (bool_dictionary.count(continue_) == 0) 
	{
		std::cout << "Хотите продолжить?" << std::endl;
		std::cout << "Ввод> ";
		std::getline(std::cin, continue_, '\n');
	}
	return bool_dictionary[continue_];
}

void admin_options::update_user()
{
	auto SQLtext = get_update_SQLtext();
	connection conn("Taxi.sqlite3");
	conn.execute(SQLtext);
}

std::string admin_options::get_update_SQLtext()
{
	auto exit = false;
	std::string column;
	std::string  login = ask_login();
	while (!exit)
	{
		switch (ask_what_update())
		{
		case 1:
			column = "name";
			exit = true;
			break;			
		case 2:
			column = "surname";
			exit = true;
			break;
		case 3:
			column = "login";
			exit = true;
			break;
		case 4:
			column = "password";
			exit = true;
			break;
					
		default:
			std::cout << "Ошибка ввода! Поробуйте ещё раз." << std::endl;
			break;
		}
	}
	return form_update(login, column, ask_value(column));
}

int admin_options::ask_what_update()
{
	auto update = -1;
	while (update == -1)
	{
		std::string tmp;
		std::cout << "1) Редактировать имя" << std::endl;
		std::cout << "2) Редактировать фамилию" << std::endl;
		std::cout << "3) Сменить логин" << std::endl;
		std::cout << "4) Сменить пароль" << std::endl;
		std::cout << "Ввод> ";
		std::getline(std::cin, tmp, '\n');
		try	{
			update = std::stoi(tmp);
		}
		catch (std::invalid_argument& e) {
			std::cout << "Ошибка ввода! Поробуйте ещё раз.";
		}
	}
	return update;	
}

std::string admin_options::ask_value(const std::string& column)
{
	std::string value;
	std::cout << "Задайте новое значение " << column << ": ";
	std::getline(std::cin, value, '\n');
	return value;
}

std::string admin_options::ask_login()
{
	std::string login;
	std::cout << "введите логин пользователя: ";
	std::getline(std::cin, login, '\n');
	return login;
}

void admin_options::write_request()
{
	if (!ask_to_continue_unsafe())
		return;

	std::string req;
	std::cout << "Текст запроса: ";
	std::getline(std::cin, req, '\n');
	connection conn("Taxi.sqlite3");
	conn.execute(req);
}

void admin_options::load_request()
{
	if (!ask_to_continue_unsafe())
		return;

	auto request = load_from_file();
	connection conn("Taxi.sqlite3");
	conn.execute(request);
}

std::string admin_options::load_from_file()
{	
	std::string request; 
	std::string filename = ask_file_name();
	std::ifstream file(filename);
	if (!file.is_open())
		throw bad_file(filename);
	std::getline(file, request);
	return request;
}

std::string admin_options::ask_file_name()
{
	std::string file_name;
	std::cout << "Полное имя файла: ";
	std::getline(std::cin, file_name, '\n');
	return file_name;
}

bool admin_options::ask_to_continue_unsafe()
{
	std::string continue_ = "null";
	std::cout << "Внимание! Правильность команд не регулироется программой!" << std::endl;
	std::cout << "Выполнение направильно сформированного запроса может привести к неожиданнм результатам" << std::endl;
	while (bool_dictionary.count(continue_) == 0) 
	{
		std::cout << "Желаете продолжить?" << std::endl;
		std::cout << "Ввод> ";
		std::getline(std::cin, continue_, '\n');
	}
	return bool_dictionary[continue_];
}

std::string admin_options::form_insert_user(const logging_data& data, const credentials& credits, const int& role)
{
	return "INSERT INTO users (login, password, name, surname, role) " \
		    "VALUES ('" +  data.login + "', '" + data.password + "', '" + credits.name + "', '" + credits.surname + "', " + std::to_string(role) + ")";
}

std::string admin_options::form_print_users(const credentials& credits, const int& role)
{
	return "SELECT * FROM users WHERE name like '" + credits.name  + "' and surname like '" + credits.surname + "' and role = " + std::to_string(role);
}

std::string admin_options::form_print_users(const credentials& credits)
{
	return "SELECT * FROM users WHERE name like '" + credits.name + "' and surname like '" + credits.surname + "' ";  	
}

std::string admin_options::form_print_users(const int& role)
{
	return "SELECT * FROM users WHERE role = " + std::to_string(role);	
}

std::string admin_options::form_print_users()
{
	return "SELECT * FROM users";
}

std::string admin_options::form_delete(const std::string& login)
{
	return "DELETE FROM users WHERE login = '" + login + "'";
}

std::string admin_options::form_update(const std::string& login, const std::string& column, const std::string& value)
{
	return "UPDATE users SET " + column + " = '" + value + "' WHERE login = '" + login + "'";	
}

int admin_options::select_callback(void* not_used, int argc, char** argv, char** columns)
{
	std::cout << "-------------------------" << std::endl;
    for (auto i = 0; i < argc; i++) {    
    	std::cout << columns[i] << ": " << argv[i] << std::endl;
    }
	std::cout << "-------------------------" << std::endl;
    return 0; 
}

admin_options::admin_options(user* current) : current_(*current)
{
	delete current;
	current = nullptr;
}
