#include "cubiecube.hpp"
#include "utils.hpp"


void check_identity()
{
	cubiecube_t* moves = get_moves();
	cubiecube_t one;
	cubiecube_t two;
	cubiecube_t three;

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

int main()
{
	cubiecube_t* moves = get_moves();
	cubiecube_t eo = create_cubie_with_edge_orientation_coord(1245);
	cubiecube_t co = create_cubie_with_corner_orientation_coord(1111);
	cubiecube_t test;

	// cubiecube_t test = {{URF, UFL, ULB, UBR, DFR, DLF, DBL, DRB}, {0, 0, 0, 0, 0, 0, 0, 0}, {UR, UR, UR, UR, UR, UR, UR, FL, FR, BL, UR, BR}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
	// cubiecube_t test = {{URF, UFL, ULB, UBR, DFR, DLF, DBL, DRB}, {0, 0, 0, 0, 0, 0, 0,  {UR, UF, UL, UB, DR, DF, DL, DB, FR, FL, BL, BR}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};


	// std::cout << std::endl;
	// std::cout << std::endl;

	std::cout << std::endl;

	
	
	
	for (int i = 0; i < 494; i ++)
	{
		test = create_cubie_with_UD_slice_coord(i);
		std::cout << UD_slice_coordinate(&test) << std::endl;

	}
}