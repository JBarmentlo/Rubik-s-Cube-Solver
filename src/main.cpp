#include "cubiecube.hpp"

int main()
{
	cubiecube_t* moves = get_moves();
	cubiecube_t	 R = moves[1];
	std::cout << corner_orientation_coordinate(&R) << std::endl;
	std::cout << edge_orientation_coordinate(&R) << std::endl;
	std::cout << corner_permutation_coordinate(&R) << std::endl;
	std::cout << edge_permutation_coordinate(&R) << std::endl;

}