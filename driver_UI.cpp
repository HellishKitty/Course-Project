#include "driver_UI.hpp"
#include <iostream>


int driver_UI::main()
{
	char option;
	while (true)
	{
		system("cls");
		option = ask_option();
		if (option == '0')
			break;
		try_perform_option(option);
		wait_to_continue();
	}
	return EXIT_SUCCESS;
}

char driver_UI::ask_option()
{
	std::string option;
	std::cout << "1) Редактировать данные о себее" << std::endl;
	std::cout << "2) Сменить пароль" << std::endl;
	std::cout << "0) Выйти из аккаунта" << std::endl;
	std::cout << "Ввод>";
	std::getline(std::cin, option, '\n');
	return option[0];
}

void driver_UI::try_perform_option(char option)
{
	try
	{
		switch (option)
		{		
		case '1':
			options_.edit_credentials();
			break;
		case '2':
			options_.change_password();
			break;
		}
	}
	catch (...)	{
		std::cout << "Возникла неизвестная ошибка!" << std::endl;
	}	
}

driver_UI::driver_UI(user* current) : options_(current)
{
		current_ = current;
}
