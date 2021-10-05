#include "Node.hpp"
#include "ida.hpp"

#include "cubiecube_utils.hpp"
#include "CubieCube.hpp"
#include "tests.hpp"
#include "move_tables.hpp"


int main()
{
	// cubiecube_t* moves = get_moves();
	// check_set_get_coord_equivalency(UD_slice_coordinate, set_UD_slice_coord, 495);
	// make_all_move_tables();

	int* corner_h_table = create_heuristics_table(N_CORNER_ORI, read_corner_orientation_move_table);
	int* UD_slice_h_table = create_heuristics_table(N_UD, read_UD_move_table);
	int* edge_h_table = create_heuristics_table(N_EDGE_ORI, read_edge_orientation_move_table);

}