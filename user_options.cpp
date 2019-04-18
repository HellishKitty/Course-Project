#include "user_options.hpp"
#include "options_exception.hpp"
#include "connection.hpp"
#include <iostream>
#define RAND_MAX 10


void user_options::edit_credentials()
{
	auto credits = ask_new_credentials();
	auto SQLtext = form_update_credits(credits);
	update(SQLtext);
}

credentials user_options::ask_new_credentials() const
{
	credentials credits;
	std::cout << "¬ведите им€: ";
	std::getline(std::cin, credits.name, '\n');
	std::cout << "введите фамилию: ";
	std::getline(std::cin, credits.surname, '\n');
	return credits;
}

void user_options::change_password()
{
	auto password = ask_new_password();
	auto SQLtext = form_update_password(password);
	update(SQLtext);
}

void user_options::update(const std::string& SQLtext)
{
	connection conn("Taxi.sqlite3");
	conn.execute(SQLtext);
}

std::string user_options::ask_new_password() const
{
	std::string password;
	std::cout << "¬ведите пароль: ";
	std::getline(std::cin, password, '\n');
	return password;
}

std::string user_options::form_update_credits(const credentials& credits) const
{
	return "UPDATE users SET name = '" + credits.name + "', surname = '" + credits.surname + "' WHERE login = '" + current_user_.get_login() + "'";
}

std::basic_string<char> user_options::form_update_password(const std::basic_string<char>& password) const
{
	return "UPDATE users SET password = '" + password + "' WHERE login = '" + current_user_.get_login() + "'";
}

user_options::user_options(user* current) : current_user_(*current)
{
	delete current;
	current = nullptr;
}
