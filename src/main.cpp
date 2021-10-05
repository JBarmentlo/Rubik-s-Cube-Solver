#include "cubiecube.hpp"
#include "Node.hpp"
#include "ida.hpp"

#include "cubiecube_utils.hpp"
#include "CubieCube.hpp"
#include "CoordCube.hpp"


#include "utils.hpp"
#include "tests.hpp"
#include "move_tables.hpp"

using namespace std;

// typedef bool (is_goal_function*)(&CoordCube);

// bool phase_one_objective(&CoordCube)
// {
// 	if (CoordCube.corner_orientation_coord != 0)
// 	{
// 		return (false);
// 	}
// 	if (CoordCube.edge_orientation_coord != 0)
// 	{
// 		return (false);
// 	}
// 	if (CoordCube.UD_slice_coord != 0)
// 	{
// 		return (false);
// 	}
// 	else
// 	{
// 		return (true);
// 	}
// }


int main()
{
	// make_raw_move_table(corner_orientation_coordinate, set_corner_orientation_coord, N_CORNER_ORI, "../tables/corner_ori_move");
    // make_raw_move_table(UD_slice_coordinate, set_UD_slice_coord, N_UD, UD_SLICE_NAME);
    // make_raw_move_table(edge_orientation_coordinate, set_edge_orientation_coord, N_EDGE_ORI, EDGE_ORI_NAME);
	

	int move;
	CoordCube* mommy_cube = new CoordCube();
	CoordCube *bb_cube;

	move = 1;

	mommy_cube->set_solved();
	bb_cube = create_baby_from_move(mommy_cube, move);
	bb_cube = create_baby_from_move(bb_cube, 2);
	bb_cube = create_baby_from_move(bb_cube, 9);
	bb_cube = create_baby_from_move(bb_cube, 8);


	Node *start = new Node(0, 0, bb_cube);

	// is_goal_function	is_goal = phase_one_objective;


	ida(start, mommy_cube);

}