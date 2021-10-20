#include "kociemba.hpp"
#include "utils.hpp"


int main(int argc, char **argv)
{
	std::vector<int> shuffle;
	if (parse_arguments(argc, argv, &shuffle) == false)
		return (false);
	kociemba(shuffle);
	return (true);
}
