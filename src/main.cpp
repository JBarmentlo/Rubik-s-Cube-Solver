#include "Node.hpp"
#include "ida.hpp"

#include "cubiecube_utils.hpp"
#include "CubieCube.hpp"
#include "CoordCube.hpp"
#include "tests.hpp"
#include "move_tables.hpp"


int main()
{
	cubiecube_t* moves = get_moves();
	// make_raw_move_table(corner_orientation_coordinate, set_corner_orientation_coord, N_CORNER_ORI, "../tables/corner_ori_move");
    // make_raw_move_table(UD_slice_coordinate, set_UD_slice_coord, N_UD, UD_SLICE_NAME);
    // make_raw_move_table(edge_orientation_coordinate, set_edge_orientation_coord, N_EDGE_ORI, EDGE_ORI_NAME);
	

	CoordCube *bb_cube = new CoordCube();

	Node *start = new Node(0, 0, bb_cube);

	// ida(start, corner_heuristic);
	create_corner_heuristic_table(N_CORNER_ORI, read_corner_orientation_move_table);

}