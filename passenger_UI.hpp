#pragma once
#include "UI.hpp"
#include "passenger_options.hpp"


class passenger_UI : public UI
{
	passenger_options options_;
public:
	int main() override;
private:
	char ask_option() override;
	void try_perform_option(char option) override;
public:
	explicit passenger_UI(user* current);
	~passenger_UI() = default;
};
