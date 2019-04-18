#include "program.hpp"


int main()
{
	auto Program = program();
	Program.init_db_if_not_exists("Taxi.sqlite3");
	Program.main();
	return EXIT_SUCCESS;
}
