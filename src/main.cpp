// #include "Node.hpp"
// #include "ida.hpp"

// #include "cubiecube_utils.hpp"
// #include "CubieCube.hpp"
// #include "tests.hpp"
// #include "move_tables.hpp"
#include "heuristics_tables.hpp"


int		main(void)
{
	// cubiecube_t* moves = get_moves();
	// check_set_get_coord_equivalency(UD_slice_coordinate, set_UD_slice_coord, 495);
	// make_all_move_tables();

	// CoordCube *bb_cube = new CoordCube();

	// bb_cube->print();
	// std::cout << "\n";
	// check_set_get_coord_equivalency(UD_slice_coordinate, set_UD_slice_coord, 495);

	// int move[] = {1, 2, 9, 8};

	// for(auto i : move)
	// 	bb_cube->apply_move(i);

	// bb_cube->print();
	// std::cout << "\n";

	// Node *start = new Node(0, 0, bb_cube);
	// check_all_coords();
	// make_all_move_tables();

	// is_goal_function is_goal = corner_heuristic;


	// ida(start, corner_heuristic);
	// Node *start = new Node(0, 0, bb_cube);

	// ida(start, corner_heuristic);
	// create_corner_heuristic_table();
	// int* corner_h_table = create_heuristics_table(N_CORNER_ORI, read_corner_orientation_move_table);
	// int* UD_slice_h_table = create_heuristics_table(N_UD, read_UD_move_table);
	// int* edge_h_table = create_heuristics_table(N_EDGE_ORI, read_edge_orientation_move_table);
	make_corner_heuristics_table();
	make_edge_heuristics_table();
	make_UD_slice_heuristics_table();
	return true;
}