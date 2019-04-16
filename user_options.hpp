#pragma once
#include "user.hpp"


typedef class user_options
{	
public:	
	static void edit_credentials(const std::string& login);
	static void change_password(const std::string& login);	
private:	
	static credentials ask_new_credentials();
	static void update(const std::string& SQLtext);
	static std::string ask_new_password();

	static std::string form_update_credits(const credentials& credits, const std::string& login);
	static std::string form_update_password(const std::string& password ,const std::string& login);
	
} options;
