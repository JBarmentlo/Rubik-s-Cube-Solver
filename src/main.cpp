#include "cubiecube.hpp"

int main()
{
	cubiecube_t* moves = get_moves();
	cubiecube_t one;
	cubiecube_t two;
	cubiecube_t three;


	// print_corners(&homecube);
	// print_corners(&R);
	// apply_move(&R, &R);
	// print_corners(&R);
	// print_corners(&moves[1]);
	// std::cout << std::endl;
	// print_edges(&homecube);
	// std::cout << std::endl;
	// // c = create_cubie_with_corner_coord(49);
	

	// std::cout << corner_orientation_coordinate(&c) << std::endl;
	// std::cout << edge_orientation_coordinate(&c) << std::endl;
	// std::cout << corner_permutation_coordinate(&c) << std::endl;
	// std::cout << edge_permutation_coordinate(&c) << std::endl;
	// std::cout << UD_slice_coordinate(&c) << std::endl;


	for (int i = 0; i < 6; i++)
	{
		one = moves[i];
		two = moves[i + 6];
		three = moves[i + 12];
		std::cout << std::endl;

		apply_move(&one, &three);
		print_corners(&one);
		one = moves[i];
		std::cout << std::endl;


		apply_move(&three, &one);
		print_corners(&three);
		three = moves[i + 12];
		std::cout << std::endl;


		apply_move(&two, &two);
		print_corners(&two);
		two = moves[i + 6];
		std::cout << std::endl;
		std::cout << std::endl;

	}

}