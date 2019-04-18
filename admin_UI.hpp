#pragma once
#include "UI.hpp"
#include "admin.hpp"


class admin_UI : public UI
{
	admin_options options_;
public:
	int main() override;
private:
	char ask_option() override;
	void try_perform_option(char option) override;
public:
	explicit admin_UI(user* current);
	~admin_UI() = default;
};
