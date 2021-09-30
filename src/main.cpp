#include "cubiecube.hpp"

int main()
{
	cubiecube_t* moves = get_moves();
	cubiecube_t	 R = moves[1];
	cubiecube_t c = moves[1];
	print_corners(&homecube);
	std::cout << std::endl;
	print_edges(&homecube);
	std::cout << std::endl;

	

	std::cout << corner_orientation_coordinate(&homecube) << std::endl;
	std::cout << edge_orientation_coordinate(&homecube) << std::endl;
	std::cout << corner_permutation_coordinate(&homecube) << std::endl;
	std::cout << edge_permutation_coordinate(&homecube) << std::endl;
	std::cout << UD_slice_coordinate(&homecube) << std::endl;


}