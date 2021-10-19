// #include "kociemba.hpp"
#include "define.hpp"
#include <stdlib.h>
#include "utils.hpp"


bool	parse_arguments(int argc, char **argv)
{
	if (argc <= 1 or argc > 2)
	{
		std::cout << USAGE;
		return (false);
	}
	if (argc == 2)
	{
		int moves = atoi(argv[1]);

		if (moves == 0 and argv[1][0] != '0')
		{
			std::cout << USAGE;
			return (false);
		}
		else
		{
			std::vector<int> shuffle = create_random_shuffle(moves);
			for (int i = 0; i < shuffle.size(); i++)
			{
				std::cout << "[" << shuffle[i] << "]" << std::endl;
			}
		}

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
