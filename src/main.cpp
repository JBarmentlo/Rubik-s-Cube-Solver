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


int main()
{
	// make_raw_move_table(corner_orientation_coordinate, set_corner_orientation_coord, N_CORNER_ORI, "../tables/corner_ori_move");
    // make_raw_move_table(UD_slice_coordinate, set_UD_slice_coord, N_UD, UD_SLICE_NAME);
    // make_raw_move_table(edge_orientation_coordinate, set_edge_orientation_coord, N_EDGE_ORI, EDGE_ORI_NAME);

	// int move;
	// CubieCube	cmp;
	// coord_cube_t mommy_cube;
	// coord_cube_t bb_cube;

	// set_solved(&mommy_cube);

	// move = 0;
	// while (move < N_MOVES)
	// {
	// 	cmp.set_solved();
	// 	cmp.multiply(&get_moves()[move]);

	// 	std::cout << "*******\nCUBICUBE:\n";
	// 	std::cout << cmp.corner_ori_coord() << std::endl;
	// 	std::cout << cmp.edge_ori_coord() << std::endl;
	// 	std::cout << cmp.UD_coord() << "\n\n\n";

	// 	bb_cube = create_baby_from_move(mommy_cube, move);

	// 	std::cout << "COORDCUBE:\n";
	// 	std::cout << bb_cube->corner_orientation_coord << std::endl;
	// 	std::cout << bb_cube->edge_orientation_coord << std::endl;
	// 	std::cout << bb_cube->UD_slice_coord << "\n\n\n";

	// 	move += 1;
	// }	

	int move;
	CoordCube *goal = new CoordCube();
	CoordCube *mommy_cube = new CoordCube();
	CoordCube *bb_cube = new CoordCube();
	Node	*test = new Node(0, 0, mommy_cube);


	move = 0;


	set_solved(goal);
	set_solved(mommy_cube);
	bb_cube = create_baby_from_move(mommy_cube, move);

	bb_cube->print();
	std::cout << endl;
	mommy_cube->print();


	if (*bb_cube == *mommy_cube)
	{
		std::cout << "mommy and baby the same\n";
	}
	else
	{
		std::cout << "not the same\n";
	}

	// ida(start, goal);

}