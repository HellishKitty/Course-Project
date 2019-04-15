#include "passenger_exception.hpp"


char const* passenger_exception::what() const
{
	return "Unknown error occured!";	
}

char const* bad_order_id::what() const
{
	return "Cant generate order ID!";	
}
