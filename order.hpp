#pragma once
#include "user.hpp"
#include <string>
#include <map>

const int COMPLETED = 2;
const int DECLINED = 1;
const int NOT_APPEARED = 0;
class user;


struct order_info
{
	std::string from_address;
	std::string to_address;
	int cost;
	int status;
	int order_id;

	static std::map<int, std::string> status_map;
	friend std::ostream& operator<< (std::ostream& stream, const order_info& out);
};

class order final
{
	credentials driver_;
	credentials passenger_;
	order_info info_;

public:
	
	order(const credentials& driver, const credentials& passenger, const order_info& info);
	~order() = default;
	friend std::ostream& operator<< (std::ostream& stream, const order& out);
};
