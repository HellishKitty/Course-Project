#include "admin_UI.hpp"
#include "database_exception.hpp"
#include <iostream>


int admin_UI::main()
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

char admin_UI::ask_option()
{
	std::string option;
	std::cout << "1) Вывести на экран список пользователей" << std::endl;
	std::cout << "2) Добавить аккаунт пользователя" << std::endl;
	std::cout << "3) Изменить данные о пользователе" << std::endl;
	std::cout << "4) Удалить акаунт пользователя | Небезопасная операция!" << std::endl;
	std::cout << "5) Выполнить свой запрос | Небезопасная операция!" << std::endl;
	std::cout << "6) Загрузить запрос из файла | Небезопасная операция!" << std::endl;
	std::cout << "0) выйти из аккаунта" << std::endl;
	std::cout << "Ввод>";
	std::getline(std::cin, option, '\n');
	return option[0];
}

void admin_UI::try_perform_option(char option)
{
	try
	{
		switch (option)
		{
		case '1':
			options_.select_users();
			break;
		case '2':
			options_.add_user();
			break;
		case '3':
			options_.update_user();
			break;
		case '4':
			options_.delete_user();
			break;
		case '5':
			options_.write_request();
			break;
		case '6':
			options_.load_request();
			break;
		}
	}
	catch (database_exception& e) {
		std::cout << e.what() << std::endl;
	}
	catch (...)	{
		std::cout << "Возникла неизвастная ошибка!" << std::endl;
	}
}

admin_UI::admin_UI(user* current) : options_(current)
{
	current_ = current;
	
}
