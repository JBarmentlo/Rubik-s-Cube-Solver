#include "kociemba.hpp"
// #include <vector>
// #include <iostream>


// void  deyas_part(void)
// {
// 	CubieCube cubie;
// 	CoordCube test(0);

// 	int solution_length = 0;
// 	int move = 0;
// 	queue<int> path;

//   	cubie.set_solved(); // all coords are set to 0

// //   APPLYING STARTING MOVES TO CUBIECUBE AND COORDCUBE:

// 	for (unsigned int i = 0; i < 100000; i++)
// 	{
// 		move = (std::rand()) % 18;
// 		test.apply_move_phase_one(move);
// 		apply_move(&cubie.data, move);
// 	}

// 	std::cout << "\n**Coordcube:**" << std::endl;
// 	test.print_coords_phase1();
// 	std::cout << "\n**Cubiecube:**" << std::endl;
// 	cubie.print_coords_phase1();

	
// 	phase_one_solver(test, 0, &path);
// 	solution_length += path.size();
// 	//  applying phase 1 path to the cubie to get the starting coords for phase 2:
// 	while (not path.empty())
// 	{
// 		std::cout << "[" << path.front() << "]";
// 		// test.apply_move_phase_two(path.front());
// 		apply_move(&cubie.data, path.front());
// 		path.pop();
// 	}
// 	std::cout << "\n" << std::endl;
// 	std::cout << "\nCUBIE AFTER PHASE ONE:" << std::endl;
// 	cubie.print_all_coords();
// 	test.set_solved();
// 	test.set_coords_phase_two(cubie.corner_perm_coord(), cubie.edge_perm_coord_2(), cubie.UD2_coord());
// 	std::cout << "\nCOORDCUBE AFTER PHASE ONE:" << std::endl;
// 	test.print_all_coords();


// 	// PHASE 2:
// 	std::cout << "\n\nENTERING PHASE 2:\n";
// 	vector<int> path2;
// 	Node *start = new Node(0, 0, &test);


// 	path2 = ida(start, phase_two_goal, phase_2_heuristic, g_plusone, create_baby_from_move_phase_two);
// 	print_path(path2);

// 	for (size_t i = 0; i < path2.size(); i++)
// 		apply_move(&cubie.data, path2[i]);

// 	// SUPPOSED RESOLVED CUBE:
// 	std::cout << "\n\nCUBIE AFTER PHASE TWO:" << std::endl;
// 	cubie.print_all_coords();
// 	solution_length += path2.size();
// 	std::cout << "\nTOTAL PATH LENGTH: " << solution_length << std::endl;

// }


int main()
{
	// parse_args;
	// result = kociemba (args.shuffle);
	std::vector<int> shuffle{4, 8, 9, 5, 18, 6, 7, 8, 2, 17, 3};
	kociemba(shuffle);
	// display_retulst;
}
