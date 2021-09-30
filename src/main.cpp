#include "cubiecube.hpp"

int main()
{
	cubiecube_t* moves = get_moves();
	cubiecube_t	 R = moves[1];
	cubiecube_t c = moves[1];
	print_corners(&c);
	print_edges(&c);
	std::cout << std::endl;

	apply_move(&c, &R);
	print_corners(&c);
	print_edges(&c);
	std::cout << std::endl;

	apply_move(&c, &R);
	print_corners(&c);
	print_edges(&c);
	std::cout << std::endl;

	apply_move(&c, &R);
	print_corners(&c);
	print_edges(&c);
	std::cout << std::endl;

	apply_move(&c, &R);
	print_corners(&c);
	print_edges(&c);
	std::cout << std::endl;

	std::cout << corner_orientation_coordinate(&c) << std::endl;
	std::cout << edge_orientation_coordinate(&c) << std::endl;
	std::cout << corner_permutation_coordinate(&c) << std::endl;
	std::cout << edge_permutation_coordinate(&c) << std::endl;

}