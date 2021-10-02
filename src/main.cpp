#include "cubiecube_utils.hpp"
#include "CubieCube.hpp"

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

		apply_move(&one, &three);
		print_corners(&one);
		print_edges(&one);
		one = moves[i];
		std::cout << std::endl;


		apply_move(&three, &one);
		print_corners(&three);
		print_edges(&three);
		three = moves[i + 12];
		std::cout << std::endl;


		apply_move(&two, &two);
		print_corners(&two);
		print_edges(&two);
		two = moves[i + 6];
		std::cout << std::endl;
		std::cout << std::endl;
	}
}


void check_identity_class()
{
	cubiecube_t* moves = get_moves();
	cubiecube_t one;
	cubiecube_t two;
	cubiecube_t three;

	CubieCube	cubo;
	cubo.set_solved();

	cubo.print_corners();
	cubo.print_edges();
	std::cout << std::endl;
	std::cout << std::endl;

	for (int i = 0; i < 6; i++)
	{
		std::cout << i << std::endl;

		one = moves[i];
		two = moves[i + 6];
		three = moves[i + 12];
		std::cout << std::endl;


		cubo.set_solved();
		cubo.multiply(&one);
		cubo.multiply(&three);
		cubo.print_corners();
		std::cout << std::endl;
		cubo.print_edges();
		std::cout << std::endl;

		cubo.set_solved();
		cubo.multiply(&two);
		two = moves[i + 6];
		cubo.multiply(&two);
		cubo.print_corners();
		std::cout << std::endl;
		cubo.print_edges();
		std::cout << std::endl;
		std::cout << std::endl;
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

	check_identity();
	// std::cout << std::endl;
	// std::cout << std::endl;

}