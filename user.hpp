#pragma once
#include <string>
#include <map>

const int ADMIN = 0;
const int DRIVER = 1;
const int PASSENGER = 2;

struct logging_data
{
	std::string login;
	std::string password; 
};

struct credentials
{
	std::string name;
	std::string surname;

	friend std::ostream& operator<< (std::ostream& stream, const credentials& out); 
};

class user final
{
	logging_data logging_;
	credentials credentials_;
	int role;

public:
	static std::map<int, std::string> role_map;

	friend std::ostream& operator<< (std::ostream& stream, const user& out);
	user(const logging_data& data, const credentials& credits);
	~user() = default;
};
