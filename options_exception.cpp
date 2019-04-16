#include "options_exception.hpp"


char const* options_exception::what() const
{
	return "Unknown error occured!";	
}

char const* bad_order_id::what() const
{
	return "Cant generate order ID!";	
}

bad_file::bad_file(const std::string& filename) noexcept :
	filename_(filename) { }

bad_file::bad_file(const bad_file& orig) noexcept :
	filename_(orig.filename_) { }

char const* bad_file::what() const
{
	return "Can't open file!";
}

std::string bad_file::error() const noexcept
{
	return "Can't open file: " + filename_;	
}
