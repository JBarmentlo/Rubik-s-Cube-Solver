#include "kociemba.hpp"

int main()
{
	std::vector<int> shuffle;
	int move;

	for (size_t i = 0; i < 50; i++)
	{
		// move = (std::rand()) % 18;
		move = i % 18;
		shuffle.push_back(move);
		std::cout << "[" << shuffle[i] << "]";
	}
	// std::vector<int> shuffle{4, 8, 9, 5, 17, 6, 7, 8, 2, 17, 3};

	kociemba(shuffle);
}
