#pragma once
#include <string>
#include "user.hpp"


class UI
{
protected:
	user* current_ = nullptr;
public:
	virtual int main() = 0;
	virtual char ask_option() = 0;
	virtual void try_perform_option(char option) = 0;
	virtual ~UI() = default;
	static void hello_screen(const user& current);
	static void wait_to_continue();
};
