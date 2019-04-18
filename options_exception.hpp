#pragma once
#include <exception>
#include <string>


class options_exception : std::exception
{
public:
	char const* what() const override;
};

class bad_order_id : options_exception
{
public:
	char const* what() const override;
};

class bad_file : options_exception
{
	std::string filename_;
public:
	char const* what() const override;
	std::string error() const noexcept;

	explicit bad_file(const std::string& filename) noexcept;
	bad_file(const bad_file& orig) noexcept;
	~bad_file() = default;
};
