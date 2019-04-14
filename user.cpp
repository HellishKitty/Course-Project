#include "user.hpp"
#include <iostream>

std::ostream& operator<<(std::ostream& stream, const credentials& out)
{
	stream << out.name << " " << out.surname;
	return stream;	
}

std::ostream& operator<<(std::ostream& stream, const user& out)
{
	stream << out.credentials_ << ", " << user::role_map[out.role];
	return stream;
}

std::map<int , std::string> user::role_map = {
	{ADMIN, "an admin"},
	{DRIVER, "a driver"},
	{PASSENGER, "a passenger"}
};
