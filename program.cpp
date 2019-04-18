#include "program.hpp"
#include "admin_UI.hpp"
#include "connection.hpp"
#include <iostream>
#include "passenger_UI.hpp"
#include "driver_UI.hpp"


int program::main()
{
	while (true)
	{
		system("cls");
		auto option = ask_logging_option();
		if (option == '0')
			break;
		auto current = try_prefrorm_option(option);
		if (current != nullptr)
			start_UI(current);
		UI::wait_to_continue();
	}
	return EXIT_SUCCESS;
}

char program::ask_logging_option() const
{
	std::string option;
	std::cout << "1) Sign in || 2) Sign up || 0) Exit" << std::endl;
	std::cout << "Input>";
	std::getline(std::cin, option, '\n');
	return option[0];
}

user* program::try_prefrorm_option(char option) const
{
	user* current = nullptr;
	try {
	
		switch (option)
		{
		case '1':
			current = logging_options_->sign_in();
			if (current == nullptr)
				std::cout << "No such combination of login and password!" << std::endl;
			break;
		case '2':
			current = logging_options_->sign_up();
			if (current == nullptr)
				std::cout << "Login already used!" << std::endl;
			break;
		default:
			std::cout << "There is no such an option! Try again." << std::endl;
			break;
	}
	} catch (...) {
		std::cout << "Unknown error occured!" << std::endl;
	}
	return current;
}

void program::start_UI(user* current)
{
	UI* ui = nullptr;
	switch (current->get_role())
	{
	case ADMIN:
		ui = new admin_UI(current);
		break;
	case DRIVER:
		ui = new driver_UI(current);
		break;
	case PASSENGER:
		ui = new passenger_UI(current);
		break;
	}
	if (ui != nullptr)
		ui->main();
	delete ui;
}

void program::init_db_if_not_exists(const std::string& file_name)
{
	connection conn(file_name);
	conn.execute(form_init_users());
	conn.execute(form_init_orders());
}

std::string program::form_init_users()
{
	return "CREATE TABLE IF NOT EXISTS orders ("\
			"ID INT PRIMARY KEY NOT NULL,"\
			"dlogin TEXT NOT NULL,"\
			"plogin TEXT NOT NULL,"
			"fromaddress TEXT,"\
			"toaddress TEXT,"\
			"status INT)";
}

std::string program::form_init_orders()
{
	return "CREATE TABLE IF NOT EXISTS users ("\
			"login TEXT PRIMARY KEY NOT NULL,"\
			"password TEXT NOT NULL,"\
			"name TEXT NOT NULL,"\
			"surname TEXT NOT NULL,"\
			"role INT NOT NULL)";	
}

program::program()
{
	logging_options_ = new logging_options();
}

program::~program()
{
	delete logging_options_;	
}
