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

void	print_cubiecube(cubiecube_t cubie)
{
	std::cout << "corner ori 1 = [" << corner_orientation_coordinate_1(&cubie) << "]"  << std::endl;
	std::cout << "edge ori 1 =   [" << edge_orientation_coordinate_1(&cubie) << "]"  << std::endl;
	std::cout << "UD slice 1 =   [" << UD_slice_coordinate_1(&cubie) << "]"  << std::endl;
	std::cout << "corner perm 2 =[" << corner_permutation_coordinate_2(&cubie) << "]"  << std::endl;
	std::cout << "edge perm 2 =  [" << edge_permutation_coordinate_2(&cubie) << "]"  << std::endl;
	std::cout << "UD slice 2 =   [" << UD_slice_sorted_coordinate_2(&cubie) << "]"  << std::endl;
}

bool  is_allowed_move(int move)
{
  if (is_allowed_quarter_turns[move % N_BASIC_MOVES] == false &&
      move != ((move % N_BASIC_MOVES) + N_BASIC_MOVES))
      return false;
    return true;
}

void		test()
{
	cubiecube_t cubie;

	set_solved_cubiecube(&cubie);

	std::cout << "APPLYING MOVES:" << std::endl;
	for (int i = 0; i < 18; i++)
	{
		if (is_allowed_move(i))
		{
			std::cout << "[" << i << "]";
	        apply_move(&cubie, i);
		}
	}
	std::cout  << std::endl;
	CoordCube start(cubie);

	std::cout << "CUBIE:" << std::endl;
	print_cubiecube(cubie);
	std::cout << "\nCOORDCUBE:" << std::endl;
	start.print_coords_phase2();

}


int main()
{

	// std::vector<int> shuffle{4, 8, 9, 5, 17, 6, 7, 8, 2, 17, 3};
	std::vector<int> shuffle{1, 5, 6};
	test();

	// kociemba(shuffle);
}
