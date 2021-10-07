#include "Node.hpp"
#include "ida.hpp"
#include "CoordCube.hpp"
#include "ida_utils.hpp"
#include "heuristics.hpp"
#include "heuristics_tables.hpp"


// #include "cubiecube_utils.hpp"
// #include "CubieCube.hpp"
// #include "tests.hpp"
// #include "move_tables.hpp"


int		main(void)
{
	// CoordCube *begin = new CoordCube();
	// vector <Node*> bebes;
	// Node*	test;

	// for (int i = 0; i < 10; i++)
	// {
	// 	begin->apply_move(i);
	// }


	// Node *start = new Node(0, 0, begin);
	// ida(start, phase_one_goal, phase_1_heuristic, g_plusone);
	// make_corner_perm_heuristics_table();
	// make_UD_2_heuristics_table();
	make_edge_perm_heuristics_table();
	// make_all_heuristics_tables();

	// make_all_move_tables();
	return true;
}