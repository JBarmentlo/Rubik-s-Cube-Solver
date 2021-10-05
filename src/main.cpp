#include "cubiecube_utils.hpp"
#include "CubieCube.hpp"

#include "utils.hpp"
#include "tests.hpp"
#include "move_tables.hpp"

int** read_raw_move_table(int coord_max, std::string filename)
{
	int*			table;
	table = (int*)malloc(N_MOVES * (coord_max + 1) * sizeof(int));
	int**			pretty_table;
	pretty_table = (int**)malloc((coord_max + 1) * sizeof(int*));

	std::ifstream in(filename, std::ios_base::binary);
	in.read((char*)table, N_MOVES * (coord_max + 1) * sizeof(int));

	for (int i = 0; i < coord_max + 1; i++)
	{
		pretty_table[i] = &table[i * N_MOVES];
	}
	return pretty_table;
}


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
	// check_set_coords_1();
	// make_raw_move_table(corner_orientation_coordinate, set_corner_orientation_coord, N_CORNER_ORI, "../tables/corner_ori_move");
	// make_raw_move_table(UD_slice_coordinate, set_UD_slice_coord, N_UD, "../tables/UD_move");
	// make_raw_move_table(edge_orientation_coordinate, set_edge_orientation_coord, N_EDGE_ORI, "../tables/edge_ori_move");

	CubieCube cube;
	cube.set_solved();
	std::cout << std::endl;
	bool testa[40320];
	for (int i = 0; i < 40320; i++)
	{
		testa[i] = false;
	}
	
	for (int i = 0; i < 40320; i++)
	{
		set_edge_permutation_coordinate_2(&cube.data, i);
		if (edge_permutation_coordinate_2(&cube.data) != i)
		{
			std::cout << edge_permutation_coordinate_2(&cube.data) << std::endl;
			std::cout << std::endl;
		}
	}

}