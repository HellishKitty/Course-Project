#pragma once
#include <exception>


class passenger_exception : std::exception
{
public:
	char const* what() const override;
};

class bad_order_id : passenger_exception
{
public:
	char const* what() const override;
};
