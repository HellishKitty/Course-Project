#pragma once
#include "user.hpp"
#include <functional>


typedef class user_options
{	
protected:
	user current_user_;
public:	
	void edit_credentials();
	void change_password();	
	std::function<void()> edit_credentials_f = std::bind(&user_options::edit_credentials, this);
	std::function<void()> change_password_f = std::bind(&user_options::change_password, this);
protected:	
	credentials ask_new_credentials() const;
	void update(const std::string& SQLtext);
	std::string ask_new_password() const;

	std::string form_update_credits(const credentials& credits) const;
	std::string form_update_password(const std::string& password) const;

public:
	user_options(user* current);
	virtual ~user_options() = default;
} options;
