#pragma once
#include "user.hpp"


typedef class logging_options final
{
public:	
	user* sign_in();
	user* sign_up();
private:
	int register_as();
	credentials ask_credentials() const;
	logging_data ask_logging_data() const;
	static std::string form_sign_in(const logging_data& data);
	std::string form_sign_up(const logging_data& data, const credentials& credits, const int& role) const;

	static user* current_callback_data_;
	static int sign_in_callback(void* user_found, int count, char **value, char **column_name);

public:
	logging_options();
	~logging_options() = default;
	
	std::map<std::string, int> register_roles = {
	{"1", DRIVER},
	{"driver", DRIVER},
	{"2", PASSENGER},
	{"passenger", PASSENGER}
};
} logging;
