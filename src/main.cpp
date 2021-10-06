#include "Node.hpp"
#include "ida.hpp"
#include "CoordCube.hpp"
#include "ida_utils.hpp"
#include "heuristics.hpp"
// #include <algorithm>

// #include "cubiecube_utils.hpp"
// #include "CubieCube.hpp"
// #include "tests.hpp"
// #include "move_tables.hpp"


int		main(void)
{
	CoordCube *begin = new CoordCube();
	vector <Node*> bebes;
	Node*	test;

	for (int i = 0; i < 10; i++)
	{
		begin->apply_move(i);
	}


	Node *start = new Node(0, 0, begin);
	bebes = start->get_bebes(g_plusone, phase_1_heuristic);
	std::cout << "\n**********\n" << std::endl;
	test = bebes[2];
	vector <Node*> bebes2;

	bebes2 = test->get_bebes(g_plusone, phase_1_heuristic);

	for(auto baby : bebes2)
	{
		if (baby == nullptr)
		{
			std::cout << "-----------nullptr" << std::endl;
		}
		else
		{
			std::cout << baby->f << std::endl;
		}
	}
	// ida(start, phase_one_goal, phase_1_heuristic, g_plusone);
	return true;
}