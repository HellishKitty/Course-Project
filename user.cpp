#include "user.hpp"
#include "order.hpp"
#include <iostream>
#include <iomanip>

std::ostream& operator<<(std::ostream& stream, const credentials& out)
{
	stream << out.name << " " << out.surname;
	return stream;	
}

std::ostream& operator<<(std::ostream& stream, const user& out)
{
	stream << out.credentials_ << ", " << user::role_map[out.role_] << std::endl;
	return stream;
}

void user::print_orders()
{
	for (auto i = 0; i != orders_.size(); ++i)
		format_output(*orders_.at(i));
}

void user::format_output(const order& out)
{
	std::setw(25);
	std::setfill('-');
	std::cout << out;
	std::setw(25);
	std::setfill('-');
}

user::user(const logging_data& data, const credentials& credits, const int& role) : 
									logging_(data), credentials_(credits), role_(role) { }

std::map<int , std::string> user::role_map = {
	{ADMIN, "an admin"},
	{DRIVER, "a driver"},
	{PASSENGER, "a passenger"}
};
