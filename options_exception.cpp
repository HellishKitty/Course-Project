#include "options_exception.hpp"


char const* options_exception::what() const
{
	return "Возникла неизвестная ошибка!";	
}

char const* bad_order_id::what() const
{
	return "Невозможно сформировать заказ!";	
}

bad_file::bad_file(const std::string& filename) noexcept :
	filename_(filename) { }

bad_file::bad_file(const bad_file& orig) noexcept :
	filename_(orig.filename_) { }

char const* bad_file::what() const
{
	return "Невозможно окрыть файл!";
}

std::string bad_file::error() const noexcept
{
	return "невозможно открыть файл " + filename_;	
}
