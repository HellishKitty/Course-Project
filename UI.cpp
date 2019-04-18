#include "UI.hpp"
#include <iostream>
#include <conio.h>

void UI::wait_to_continue()
{
	std::cout << "Нажмите любую кнопку, чтобы продолжить..." << std::endl;
	_getch();
}

void UI::hello_screen(const user& current)
{
	std::cout << "Signed in as " << current.get_credential() << ", " << current.get_role();	
}
