// #include "kociemba.hpp"
#include "define.hpp"

bool	parse_arguments(int argc, char **argv)
{
	if (argc <= 1)
	{
		std::cout << USAGE;
		return (false);
	}
	return (true);
}

int main(int argc, char **argv)
{
	if (parse_arguments(argc, argv) == false)
		return (false);


	// kociemba(shuffle);
	return (true);
}
