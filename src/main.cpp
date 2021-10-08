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

void 	print_table_depth(int d, CoordCube cub)
{
	if (d == 0)
	{
		std::cout << phase_1_perfect_heuristic(cub) << " " ;
		if (phase_1_perfect_heuristic(cub) == UNFILLED)
		{
			std::cout << cub.flat_coord() << std::endl;
		}
		return;
	}
	for (int i = 0; i < N_MOVES; i++)
	{
		CoordCube bb1 = cub.create_baby_from_move_stack(i);
		std::cout << "move: " << i << " ";
		print_table_depth(d - 1,  bb1);
	}
	std::cout << std::endl;
}

void 	print_table_2(CoordCube cub)
{
	for (size_t i = 0; i < N_MOVES; i++)
	{
		std::cout << "MOVE: " << i << std::endl;
		CoordCube bb = cub.create_baby_from_move_stack(i);
		for (unsigned int j; j < N_MOVES; j++)
		{
			CoordCube bbb = bb.create_baby_from_move_stack(j);
			std::cout << j << ": " << bbb.flat_coord() << ": " << (int)phase_1_perfect_heuristic(bbb) << ", " << std::endl;
		}
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

int main()
{
	// backwards_fill_h_table(10);
	CoordCube cub(0);
	CoordCube start(0);
	for (int i = 0; i < 100; i++)
	{
		// std::cout << get_inverse_move_number(i) << std::endl;
		start.apply_move_phase_one(i % 18);
	}
	phase_one_solver(start, 0);

	// start.print();
	// std::cout << std::endl;
	// start.apply_move_phase_one(16);
	// start.print();
	// std::cout << std::endl;
	// start.apply_move_phase_one(4);
	// start.print();
	// for (size_t i = 0; i < N_MOVES; i++)
	// {
	// 	std::cout << i << std::endl;
	// 	CoordCube bb = cub.create_baby_from_move_stack(i);
	// 	int lol = 0;
	// 	while (lol < N_MOVES)
	// 	{
	// 		CoordCube bbb = bb.create_baby_from_move_stack(lol);
	// 		std::cout << "\t" << lol << std::endl;
	// 		int kk = 0;
	// 		while (kk < N_MOVES)
	// 		{
	// 			CoordCube l = bbb.create_baby_from_move_stack(kk);
	// 			std::cout << "\t\t" << kk << ": " << bbb.create_baby_from_move_stack(kk).flat_coord() << ": " << (int)phase_1_perfect_heuristic(l) << ", " << std::endl;
	// 			if (phase_1_perfect_heuristic(l) == 15)
	// 				std::cout << "/* message */" << std::endl;
	// 			kk = kk + 1;
	// 		}
	// 		lol = lol + 1;
	// 	}
	// 	std::cout << std::endl;

	// }
	// std::cout << get_h_filling() << std::endl; 
	// test_h();
	// test_h();
	// test_h();
	// test_h();
	// test_h();
	// test_h();
	// test_h();
	// test_h();


}