#include "Node.hpp"
#include "ida.hpp"
#include "CoordCube.hpp"
#include "ida_utils.hpp"
#include "heuristics.hpp"
#include "heuristics_tables.hpp"
#include "utils.hpp"
#include "Node.hpp"


#include "cubiecube_utils.hpp"
#include "CubieCube.hpp"
// #include "move_tables.hpp"
#include <fstream>
#include <string.h>
#include <stack>
#include <vector>

#include "define.hpp"

void  deyas_part(void)
{
  CoordCube *test = new CoordCube(); // all coords are set to 0
  CubieCube cubie;

  cubie.set_solved(); // all coords are set to 0

  // APPLYING STARTING MOVES TO CUBIECUBE AND COORDCUBE:
  for (size_t i = 0; i < 10; i++)
  {
    test->apply_move_phase_one(i);
    apply_move(&cubie.data, i);
  }
  std::cout << "\n" << std::endl;
  test->print();
  std::cout << "\n" << std::endl;
  cubie.print_all_coords();

  // RESOLVING RUBIKS: //
  Node *start = new Node(0, 0, test);
  vector<int> path;

  // PHASE 1:
  path = ida(start, phase_one_goal, phase_1_heuristic, g_plusone, create_baby_from_move_phase_one);
  print_path(path);
  std::cout << "\n" << std::endl;
  //  applying phase 1 path to the cubie to get the starting coords for phase 2:
  for (size_t i = 0; i < path.size(); i++)
    apply_move(&cubie.data, path[i]);
  // applying cubie coords to the cubecoord:
  test->corner_permutation_coord = cubie.corner_perm_coord();
  test->edge_permutation_coord = cubie.edge_perm_coord();
  test->UD_slice2_coord = cubie.UD2_coord();

  // PHASE 2:
  path = ida(start, phase_two_goal, phase_2_heuristic, g_plusone, create_baby_from_move_phase_two);
  print_path(path);
  for (size_t i = 0; i < path.size(); i++)
    apply_move(&cubie.data, path[i]);

  // SUPPOSED RESOLVED CUBE:
  std::cout << "\n" << std::endl;
  cubie.print_all_coords();
}

void  showing_what_is_wrong(void)
{
  CoordCube *test = new CoordCube(); // all coords are set to 0
  CubieCube cubie;

  cubie.set_solved(); // all coords are set to 0

  // APPLYING STARTING MOVES TO CUBIECUBE AND COORDCUBE:
  for (size_t i = 0; i < 10; i++)
  {
    test->apply_move_phase_one(i);
    apply_move(&cubie.data, i);
  }
  std::cout << "\nCOORDCUBE COORDS (phase two coords should be = to 0)" << std::endl;
  test->print();
  std::cout << "\nCUBIE CUBE COORDS (first 3 coords should be the same as COORDCUBE)" << std::endl;
  cubie.print_all_coords();
}

int		main(void)
{
  showing_what_is_wrong();
  return 0;
}

void 	print_table_depth(int d, int depth, CoordCube cub)
{
	if (d == 0)
	{
		if (phase_1_perfect_heuristic(cub) > depth)
		{
			std::cout << cub.flat_coord() << ": " << phase_1_perfect_heuristic(cub) << " " ;
		}
		return;
	}
	for (int i = 0; i < N_MOVES; i++)
	{
		CoordCube bb1 = cub.create_baby_from_move_stack(i);
		print_table_depth(d - 1, depth + 1,  bb1);
		// std::cout << "move: " << i << std::endl;
	}
}

void test_h(void)
{
	CoordCube cub(0, 0, 0);
	std::cout << "Testing ";
	std::cout << "h " << phase_1_perfect_heuristic(cub) << std::endl;
	for (int i; i <  N_MOVES; i++)
	{
		int move = rand() % 18;
		cub.apply_move_phase_one(move);
		std::cout << i << ",  " << move;
		std::cout << " h: " << phase_1_perfect_heuristic(cub) << std::endl;
		std::cout << std::endl;
	}
	
}

float			get_h_filling()
{
	unsigned int size =  N_EDGE_ORI * N_CORNER_ORI * N_UD;
	unsigned int full = 0;

	for (unsigned int i; i < size; i++)
	{
		CoordCube c = CoordCube(i);
		if (phase_1_perfect_heuristic(c) != 15)
		{
			full = full + 1;
		}
	}
	return (float(full) / float(size));
}



int		main(void)
{ 
	CoordCube *test = new CoordCube();
	CubieCube cubie;
	// make_all_move_tables();
	// make_all_heuristics_tables();

	cubie.set_solved();
	for (size_t i = 0; i < 10; i++)
	{
		test->apply_move_phase_one(i);
		apply_move(&cubie.data, i);
		test->print();
		std::cout << std::endl;
		cubie.print();
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;
	}
	std::cout << "\n" << std::endl;
	// test->print();
	Node *start = new Node(0, 0, test);

	vector<int> path;

	// path = ida(start, phase_one_goal, phase_1_heuristic, g_plusone, create_baby_from_move_phase_one);

	// for (size_t i = 0; i < path.size(); i++)
	// {
	// 	std::cout << path[i] << "-";
	// }

	// std::cout << "\n" << std::endl;
	// std::cout << "corner ori: [" << cubie.corner_ori_coord() << "]" << std::endl;
	// std::cout << "edge ori: [" << cubie.edge_ori_coord() << "]" << std::endl;
	// std::cout << "UD slice 1: [" << cubie.UD_coord() << "]" << std::endl;
	// std::cout << "corner perm: [" << cubie.corner_perm_coord() << "]" << std::endl;
	// std::cout << "edge perm: [" << cubie.edge_perm_coord() << "]" << std::endl;
	// std::cout << "UD slice2: [" << cubie.UD_coord() << "]" << std::endl;

	// for (size_t i = 1; i < path.size(); i++)
	// {
	// 	apply_move(&cubie.data, path[i]);
	// }
	// std::cout << "\n\n\n" << std::endl;
	// std::cout << "corner ori: [" << cubie.corner_ori_coord() << "]" << std::endl;
	// std::cout << "edge ori: [" << cubie.edge_ori_coord() << "]" << std::endl;
	// std::cout << "UD slice 1: [" << cubie.UD_coord() << "]" << std::endl;
	// std::cout << "corner perm: [" << cubie.corner_perm_coord() << "]" << std::endl;
	// std::cout << "edge perm: [" << cubie.edge_perm_coord() << "]" << std::endl;
	// std::cout << "UD slice2: [" << cubie.UD_coord() << "]" << std::endl;


	return 0;
}
