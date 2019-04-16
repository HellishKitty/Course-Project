#include "user_options.hpp"
#include <iostream>
#include "options_exception.hpp"
#include "connection.hpp"
#define RAND_MAX 10


void user_options::edit_credentials(const std::string& login)
{
	auto credits = ask_new_credentials();
	auto SQLtext = form_update_credits(credits, login);
	update(SQLtext);
}

credentials user_options::ask_new_credentials()
{
	credentials credits;
	std::cout << "Enter name: ";
	std::getline(std::cin, credits.name, '\n');
	std::cout << "Enter surname: ";
	std::getline(std::cin, credits.surname, '\n');
	return credits;
}

void user_options::update(const std::string& SQLtext)
{
	connection conn("Taxi.sqlite3");
	conn.execute(SQLtext);
}

void user_options::change_password(const std::string& login)
{
	auto password = ask_new_password();
	auto SQLtext = form_update_password(password, login);
	update(SQLtext);
}

std::string user_options::ask_new_password()
{
	std::string password;
	std::cout << "Enter new password: ";
	std::getline(std::cin, password, '\n');
	return password;
}

std::string user_options::form_update_credits(const credentials& credits, const std::string& login)
{
	return "UPDATE users SET name = '" + credits.name + "', surname = '" + credits.surname + "' WHERE login = '" + login + "'";
}

std::basic_string<char> user_options::form_update_password(const std::basic_string<char>& password, const std::basic_string<char>& login)
{
	return "UPDATE users SET password = '" + password + "' WHERE login = '" + login + "'";
}
