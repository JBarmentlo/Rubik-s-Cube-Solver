#include "Node.hpp"
#include "ida.hpp"
#include "CoordCube.hpp"
#include "ida_utils.hpp"
#include "heuristics.hpp"
#include "heuristics_tables.hpp"
#include "utils.hpp"
#include "Node.hpp"
#include "tests.hpp"


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

//   APPLYING STARTING MOVES TO CUBIECUBE AND COORDCUBE:
  for (size_t i = 0; i < 10; i++)
  {
	test->apply_move_phase_one(i);
	apply_move(&cubie.data, i);
  }
  std::cout << "\n" << std::endl;
  test->print();
  std::cout << "\n" << std::endl;
  cubie.print_all_coords();

//   RESOLVING RUBIKS: //
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
  test->set_solved();
  test->set_coords_phase_two(cubie.corner_perm_coord(), cubie.edge_perm_coord(), cubie.UD2_coord());
  std::cout << "\nCUBIE AFTER PHASE ONE:" << std::endl;
  cubie.print_all_coords();


  // PHASE 2:
  std::cout << "\n\n";
  path = ida(start, phase_two_goal, phase_2_heuristic, g_plusone, create_baby_from_move_phase_two);
  print_path(path);
  
  for (size_t i = 0; i < path.size(); i++)
  {
	  std::cout << "applying move: " << path[i] << std::endl;
	  apply_move(&cubie.data, path[i]);
  }
  
  // SUPPOSED RESOLVED CUBE:
  std::cout << "\n\nCUBIE AFTER PHASE TWO:" << std::endl;
  cubie.print_all_coords();
}

void	showing_whats_wrong()
{
	CoordCube *test = new CoordCube(); // all coords are set to 0
	CubieCube cubie;

	cubie.set_solved(); // all coords are set to 0

	//   APPLYING STARTING MOVES TO CUBIECUBE AND COORDCUBE:
	for (size_t i = 0; i < 18; i++)
	{
		test->set_solved();
		cubie.set_solved();
		std::cout  << std::endl;
		if (is_allowed_move_phase2(i) == true)
		{
			test->apply_move_phase_one(i);
			test->apply_move_phase_two(i);
			apply_move(&cubie.data, i);
			std::cout << "\nCOORDCUBE: applying move : " << i << std::endl;
			test->print();
			std::cout << "\nCUBIECUBE: applying move : " << i << std::endl;
			cubie.print_all_coords();
		}
	}
}


// void 	print_table_depth(int d, int depth, CoordCube cub) // TODO: Which one did you want
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
	backwards_fill_h_table(9);
	// CoordCube cub(0);
	// CoordCube start(0);
	// CubieCube cubie = CubieCube();
	// cubie.set_solved();

	// for (int i = 6; i < 13; i++)
	// {
	// 	// start.apply_move_phase_one(i % 18);
	// 	// set_edge_permutation_coordinate_2(i, &cubie.data);
	// 	cubie.multiply(&get_moves()[i % 18]);
	// 	// std::cout << edge_permutation_coordinate_2(&cubie.data) << std::endl;
	// 	std::cout << cubie.edge_perm_coord_2() << std::endl;
	// 	start.apply_move_phase_one(std::rand() % 18);

	// }
	// // check_all_coords();
	// phase_one_solver(start, 0);
	// // std::cout << get_h_filling() << std::endl;
	// // size_t s = HSIZEONE * 80L;

	// // free(test);
}
