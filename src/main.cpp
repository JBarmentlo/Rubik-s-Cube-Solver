#include "cubiecube_utils.hpp"
#include "CubieCube.hpp"

#include "utils.hpp"
#include "tests.hpp"
#include "move_tables.hpp"





int main()
{
	cubiecube_t* moves = get_moves();
	cubiecube_t eo = create_cubie_with_edge_orientation_coord(1245);
	cubiecube_t co = create_cubie_with_corner_orientation_coord(1111);
	cubiecube_t test;

	// cubiecube_t test = {{URF, UFL, ULB, UBR, DFR, DLF, DBL, DRB}, {0, 0, 0, 0, 0, 0, 0, 0}, {UR, UR, UR, UR, UR, UR, UR, FL, FR, BL, UR, BR}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
	// cubiecube_t test = {{URF, UFL, ULB, UBR, DFR, DLF, DBL, DRB}, {0, 0, 0, 0, 0, 0, 0,  {UR, UF, UL, UB, DR, DF, DL, DB, FR, FL, BL, BR}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

	// check_identity_class_edges();

	// std::cout << std::endl;
	// std::cout << std::endl;
	check_set_coords_1();
	make_raw_move_table(corner_orientation_coordinate, set_corner_orientation_coord, N_CORNER_ORI, "../tables/corner_ori_move");
	make_raw_move_table(UD_slice_coordinate, set_UD_slice_coord, N_UD, "../tables/UD_move");
	make_raw_move_table(edge_orientation_coordinate, set_edge_orientation_coord, N_EDGE_ORI, "../tables/edge_ori_move");

	CubieCube cube;
	std::cout << std::endl;
	std::cout << std::endl;

	for (int i = 0; i < 18; i++) 
	{
		cube.set_solved();
		cube.multiply(&moves[i]);
		std::cout << cube.corner_ori_coord() << std::endl;
	}

}