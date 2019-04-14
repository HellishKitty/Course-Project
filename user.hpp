#pragma once
#include <string>
#include <map>
#include <vector>
#include <memory>
#include <ostream>

const int ADMIN = 0;
const int DRIVER = 1;
const int PASSENGER = 2;
class order;

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
	int role_;
	std::vector<std::shared_ptr<order>> orders_;

	void format_output(const order& out);
public:
	static std::map<int, std::string> role_map;

	credentials get_credential() const { return credentials_; }
	void set_orders(std::vector<std::shared_ptr<order>>& orders) { orders_ = orders; }
	void print_orders();

	friend std::ostream& operator<< (std::ostream& stream, const user& out);
	user(const logging_data& data, const credentials& credits, const int& role);
	~user() = default;
};
