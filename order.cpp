#include "order.hpp"
#include "user.hpp"
#include <iostream>

std::ostream& operator<<(std::ostream& stream, const order_info& out)
{
	stream << "Form " << out.from_address << " to " << out.to_address << std::endl;
	stream << "Cost: " << out.cost << ", status: " << order_info::status_map[out.status] << std::endl;
	return stream;
}

std::ostream& operator<<(std::ostream& stream, const order& out)
{
	stream << "Driver " << out.driver_;
	stream << ", passenger " << out.passenger_;
	stream << out.info_;
	return stream;
}

order::order(const credentials& driver, const credentials& passenger, const order_info& info) :
			driver_(driver), passenger_(passenger), info_(info) { }


std::map<int , std::string> order_info::status_map = {
	{NOT_APPEARED, "passenger did not appear"},
	{DECLINED, "was declined"},
	{COMPLETED, "was completed"}
};
