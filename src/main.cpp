#include "kociemba.hpp"
#include "utils.hpp"
#include "define.hpp"
#include "deya_test.hpp"


int main(int argc, char **argv)
{
	std::vector<int> shuffle;
	std::vector<int> solution;

	if (parse_arguments(argc, argv, &shuffle) == false)
		return (false);

	for (int move: shuffle)
	{
		std::cout << "move = " << move << " o sea: " << moves_strings[move] << std::endl;
	}

	test_first_steps(shuffle);
	// solution = kociemba(shuffle);
	// std::cout << "COMPLETE PATH TO SOLUTION:" << std::endl;
	// for(auto move : solution)
	// {
	// 	std::cout << moves_strings[move] << " ";
	// }
	// std::cout << "\n\n";
	return (true);
}
