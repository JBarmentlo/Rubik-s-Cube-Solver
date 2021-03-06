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
#include <queue>

#include "define.hpp"

void  deyas_part(void)
{
	CubieCube cubie;
	CoordCube test(0);

	int solution_length = 0;
	int move = 0;
	queue<int> path;

  	cubie.set_solved(); // all coords are set to 0

//   APPLYING STARTING MOVES TO CUBIECUBE AND COORDCUBE:

	for (unsigned int i = 0; i < 100000; i++)
	{
		move = (std::rand()) % 18;
		test.apply_move_phase_one(move);
		apply_move(&cubie.data, move);
	}

	std::cout << "\n**Coordcube:**" << std::endl;
	test.print_coords_phase1();
	std::cout << "\n**Cubiecube:**" << std::endl;
	cubie.print_coords_phase1();

	
	phase_one_solver(test, 0, &path);
	solution_length += path.size();
	//  applying phase 1 path to the cubie to get the starting coords for phase 2:
	while (not path.empty())
	{
		std::cout << "[" << path.front() << "]";
		// test.apply_move_phase_two(path.front());
		apply_move(&cubie.data, path.front());
		path.pop();
	}
	std::cout << "\n" << std::endl;
	std::cout << "\nCUBIE AFTER PHASE ONE:" << std::endl;
	cubie.print_all_coords();
	test.set_solved();
	test.set_coords_phase_two(cubie.corner_perm_coord(), cubie.edge_perm_coord_2(), cubie.UD2_coord());
	std::cout << "\nCOORDCUBE AFTER PHASE ONE:" << std::endl;
	test.print_all_coords();


	// PHASE 2:
	std::cout << "\n\nENTERING PHASE 2:\n";
	vector<int> path2;
	Node *start = new Node(0, 0, &test);


	path2 = ida(start, phase_two_goal, phase_2_heuristic, g_plusone, create_baby_from_move_phase_two);
	print_path(path2);

	for (size_t i = 0; i < path2.size(); i++)
		apply_move(&cubie.data, path2[i]);

	// SUPPOSED RESOLVED CUBE:
	std::cout << "\n\nCUBIE AFTER PHASE TWO:" << std::endl;
	cubie.print_all_coords();
	solution_length += path2.size();
	std::cout << "\nTOTAL PATH LENGTH: " << solution_length << std::endl;

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
	unsigned int size =  HSIZEONE;
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
	// CoordCube cub(0);
	// CoordCube start(0);
	// queue<int> path;

	// for (unsigned int i = 0; i < 1000000; i++)
	// {
	// 	start.apply_move_phase_one((std::rand()) % 18);
	// }



	// phase_one_solver(start, 0, &path);
	// for(int i = 0; i < path.size(); i++)
	// {
	// 	std::cout << "[" << path.front() << "]";
	// 	path.pop();
	// }
	

	deyas_part();
	// backwards_fill_h_table(10);
	// CoordCube cub(0);
	// CoordCube start(0);
	// CubieCube cubie = CubieCube();
	// cubie.set_solved();
	// int move;

	// for (int i = 6; i < 13; i++)
	// {
	// 	// start.apply_move_phase_one(i % 18);
	// 	// set_edge_permutation_coordinate_2(i, &cubie.data);
		// cubie.multiply(&get_moves()[i % 18]);
	// 	// std::cout << edge_permutation_coordinate_2(&cubie.data) << std::endl;
	// 	std::cout << cubie.edge_perm_coord_2() << std::endl;
		// move = std::rand() % 18;
		// start.apply_move_phase_one(move);

	// }
	// // check_all_coords();
	// phase_one_solver(start, 0);
	// std::cout << "finished!" << std::endl;
	// // std::cout << get_h_filling() << std::endl;
	// // size_t s = HSIZEONE * 80L;

	// // free(test);
}
