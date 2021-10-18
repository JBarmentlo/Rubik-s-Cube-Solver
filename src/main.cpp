#include "kociemba.hpp"

int main()
{
	// std::vector<int> shuffle;
	int move;

	std::vector<int> shuffle{4, 6, 8, 9};

	// for (size_t i = 0; i < 50; i++)
	for(size_t i = 0; i < shuffle.size(); i++)
	{
		// move = (std::rand()) % 18;
		// move = i % 18;
		// shuffle.push_back(move);
		// std::cout << "[" << shuffle[i] << "]";
		std::cout << "[" << moves_strings[shuffle[i]] << "]";
	}

	kociemba(shuffle);
}
