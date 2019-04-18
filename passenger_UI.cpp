#include "passenger_UI.hpp"
#include <iostream>


int passenger_UI::main()
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

char passenger_UI::ask_option()
{
	std::string option;
	std::cout << "1) Заказать такси" << std::endl;
	std::cout << "2) Показать мои заказы" << std::endl;
	std::cout << "3) Редактировать данные о себе" << std::endl;
	std::cout << "4) Сменить пароль" << std::endl;
	std::cout << "0) Выйти из аккаунта" << std::endl;
	std::cout << "Ввод>";
	std::getline(std::cin, option, '\n');
	return option[0];
}

void passenger_UI::try_perform_option(char option)
{
	try
	{
		switch (option)
		{
		case '1':
			options_.order_taxi();
			break;
		case '2':
			options_.print_orders();
			break;
		case '3':
			options_.edit_credentials();
			break;
		case '4':
			options_.change_password();
			break;
		}
	}
	catch (...)	{
		std::cout << "Возникла неизвестная ошибка!" << std::endl;
	}	
}

passenger_UI::passenger_UI(user* current) : options_(current)
{
	current_ = current;	
}
