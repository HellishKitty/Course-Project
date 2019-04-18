#pragma once
#include "UI.hpp"
#include "user_options.hpp"


class driver_UI : public UI
{
	user_options options_;
public:
	int main() override;
private:
	char ask_option() override;
	void try_perform_option(char option) override;
public:
	explicit driver_UI(user* current);
	~driver_UI() = default;
};
