// #include "kociemba.hpp"
#include "define.hpp"
#include <stdlib.h>
#include "utils.hpp"


bool	parse_arguments(int argc, char **argv, std::vector<int> *shuffle)
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
			std::vector<char*> v = ft_strsplit(argv[1], ' ');
			for(auto word : v)
			{
				if (moves_numbers.find(word) == moves_numbers.end())
				{
					std::cout << USAGE;
					return (false);
				}
				shuffle->push_back(moves_numbers[word]);
			}
			return (true);
		}
		int i = 0;
		while (argv[1][i] != '\0')
		{
			if (isdigit(argv[1][i]) == false)
			{
				std::cout << USAGE;
				return (false);
			}
			i++;
		}
		*shuffle = create_random_shuffle(moves);
	}
	return (true);
}

int main(int argc, char **argv)
{
	std::vector<int> shuffle;
	if (parse_arguments(argc, argv, &shuffle) == false)
		return (false);
	for(auto move : shuffle)
	{
		std::cout << "[" << move << "]";
	}
	std::cout << "\n";

	// kociemba(shuffle);
	return (true);
}
