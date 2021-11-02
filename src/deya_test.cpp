#include "kociemba.hpp"
#include "utils.hpp"
#include "define.hpp"
#include "deya_test.hpp"

#include <iostream>

void	test_result(std::vector<int> input_shuffle, std::vector<int> output_shuffle, int phase_one_length)
{
	cubiecube_t cubie;

	std::cout << "ENTERING TEST FUNCTION (all values should be equal to 0):" << std::endl;
	set_solved_cubiecube(&cubie);

	for(auto move : input_shuffle)
		apply_move(&cubie, move);

	for(auto move : output_shuffle)
		apply_move(&cubie, move);
	
	if (is_cubiecube_goal(&cubie) == true)
		std::cout << "**** ALL GOOD ****" << std::endl;
	else
		std::cout << "!!!!! ERROR !!!!!!" << std::endl;
	print_coords_phase2(&cubie);
}


std::vector<int>	compare_coords1(CoordCube coordie1, cubiecube_t cubie1)
{
	std::vector<int> coords1;

	if ((corner_orientation_coordinate_1(&cubie1) != coordie1.corner_orientation_coord_1)
	or (edge_orientation_coordinate_1(&cubie1) != coordie1.edge_orientation_coord_1)
	or (UD_slice_coordinate_1(&cubie1) != coordie1.UD_slice_coord_1))
	{
		std::cout << "ERROR: different coords after first shuffle" << std::endl;
	}
	else
	{
		std::cout << "GOOD AFTER FIRST SHUFFLE" << std::endl;
		coords1 = {coordie1.corner_orientation_coord_1, coordie1.edge_orientation_coord_1, coordie1.UD_slice_coord_1};
	}
	return (coords1);
}


std::vector<int>	compare_coords_after_phase1(CoordCube coordie1, cubiecube_t cubie1)
{
	std::vector<int> coords2;

	if ((corner_orientation_coordinate_1(&cubie1) != coordie1.corner_orientation_coord_1)
	or (edge_orientation_coordinate_1(&cubie1) != coordie1.edge_orientation_coord_1)
	or (UD_slice_coordinate_1(&cubie1) != coordie1.UD_slice_coord_1))
	{
		std::cout << "ERROR: different coords after first shuffle" << std::endl;
	}
	else
	{
		std::cout << "GOOD AFTER FIRST PHASE" << std::endl;
		coords2 = {corner_permutation_coordinate_2(&cubie1), edge_permutation_coordinate_2(&cubie1), UD_slice_sorted_coordinate_2(&cubie1)};
	}
	return (coords2);
}


std::vector<int>	compare_coords_after_phase2(CoordCube coordie1, cubiecube_t cubie1)
{
	std::vector<int> coords2;

	if ((corner_permutation_coordinate_2(&cubie1) != coordie1.corner_permutation_coord_2)
	or (edge_permutation_coordinate_2(&cubie1) != coordie1.edge_permutation_coord_2)
	or (UD_slice_sorted_coordinate_2(&cubie1) != coordie1.UD_slice_coord_2))
	{
		std::cout << "ERROR: different coords after first phase" << std::endl;
	}
	else
	{
		std::cout << "GOOD AFTER PHASE 1 " << std::endl;
		coords2 = {corner_permutation_coordinate_2(&cubie1), edge_permutation_coordinate_2(&cubie1), UD_slice_sorted_coordinate_2(&cubie1)};
	}
	return (coords2);
}


std::vector<int>	from_queue_to_vec(std::queue<int> input)
{
	std::vector<int> output;

	while (input.empty() == false)
	{
		output.push_back(input.front());
		input.pop();
	}
	return (output);
}


std::vector<int>	from_stack_to_vec(std::stack<int> input)
{
	std::vector<int> output;

	while (input.empty() == false)
	{
		output.push_back(input.top());
		input.pop();
	}
	return (output);
}

void	test_phase_two(cubiecube_t cubie2)
{
	CoordCube coordie2(cubie2);

	std::cout << "\n\nCOORDIE BEFORE PHASE 2:" << std::endl;
   	coordie2.print_all_coords();

	std::cout << "\nCUBIE BEFORE PHASE 2:" << std::endl;
	print_coords_phase2(&cubie2);

	std::stack<int> path;
    phase_two_solver(coordie2, &path);

	std::vector<int> phase_two_shuffle = from_stack_to_vec(path);

    for(auto move : phase_two_shuffle)
    {
		std::cout << "applying move = " << move << std::endl;
		apply_move(&cubie2, move);
        coordie2.apply_move_phase_two(move);
    }
	std::cout << "\n\nCOORDIE AFTER PHASE 2:" << std::endl;
	coordie2.print_all_coords();

	std::cout << "\nCUBIE AFTER PHASE 2:" << std::endl;
	print_coords_phase2(&cubie2);

}


void	test_after_phase_one(CoordCube coordie1, cubiecube_t cubie1)
{
	std::cout << "\n\nCOORDIE BEFORE PHASE 1:" << std::endl;
   	coordie1.print_coords_phase1();

	std::cout << "\nCUBIE BEFORE PHASE 1:" << std::endl;
	print_coords_phase1(&cubie1);

	std::queue<int> path;
    phase_one_solver(coordie1, 0, &path);

	std::vector<int> phase_one_shuffle = from_queue_to_vec(path);

    for(auto move : phase_one_shuffle)
    {
		apply_move(&cubie1, move);
        coordie1.apply_move_phase_one(move);
    }
	std::cout << "\n\nCOORDIE AFTER PHASE 1:" << std::endl;
	coordie1.print_coords_phase1();

	std::cout << "\nCUBIE AFTER PHASE 1:" << std::endl;
	print_coords_phase2(&cubie1);

	std::vector<int> coords_before_2 = compare_coords_after_phase1(coordie1, cubie1);

	test_phase_two(cubie1);

}



void	test_first_steps(std::vector<int> input_shuffle, args_t args)
{
	CoordCube coordie(0);
	cubiecube_t cubie;

	set_solved_cubiecube(&cubie);
   	std::cout << "\n\nCOORDIE BEFORE SHUFFLE:" << std::endl;
   	coordie.print_coords_phase1();

	std::cout << "\nCUBIE BEFORE SHUFFLE:" << std::endl;
	print_coords_phase1(&cubie);

    for(auto move : input_shuffle)
    {
		apply_move(&cubie, move);
        coordie.apply_move_phase_one(move);
    }
	std::cout << "\n\nCOORDIE AFTER SHUFFLE:" << std::endl;
	coordie.print_coords_phase1();

	std::cout << "\nCUBIE AFTER SHUFFLE:" << std::endl;
	print_coords_phase1(&cubie);

	test_after_phase_one(coordie, cubie);

}


std::mutex lock;
void	phase_two_multithread_function(int start, int end, int &min, int &tmp, std::vector<CoordCube> bebes, int threshold, g_function g_func, heuristic_function heuristic, is_goal_function is_goal, std::stack<int> *path)
{
	std::lock_guard guard(lock);
	if (tmp == SUCCESS)
		return;
	for (int i = start; i < end; i++)
	{
		tmp = phase_2_search(bebes[i], threshold, g_func, heuristic, is_goal, path);
		if(tmp == SUCCESS)
		{
			std::cout << "SUCCESS *****" << std::endl;
			return; // SUCCESS
		}
		if(tmp < min)
			min = tmp;
	}
	return;
}


void	phase_two_solver_thread(CoordCube cube, std::stack<int> *path)
{
	int		i = 0;
	int		threshold = THRESHOLD_INIT;

	cube.solver_init();
	while (i < MAX_ITER)
	{
		// std::cout << "threshold = " << threshold << std::endl;
		int		min;
		int		tmp = 0;

		int f = cube.f;
		path->push(cube.origin_move);
		if(phase_two_goal(cube) == true)
			return; // SUCCESS
		if(f > threshold)
		{
			path->pop();
			return; // return f
		}
		min = MAX_INT;
		std::vector<CoordCube> bebes = cube.get_babies_phase2(g_plusone, phase_2_heuristic);
		std::cout << "Size of first babies: " << bebes.size() << std::endl;
		// TODO : path is still missing the first value
		if(bebes.empty() == false)
		{
			std::thread t1 = std::thread(&phase_two_multithread_function, 0, 3, std::ref(min), std::ref(tmp), bebes, threshold, g_plusone, phase_2_heuristic, phase_two_goal, path);
			if (tmp == SUCCESS)
				return;
			std::thread t2 = std::thread(&phase_two_multithread_function, 3, 7, std::ref(min), std::ref(tmp), bebes, threshold, g_plusone, phase_2_heuristic, phase_two_goal, path);
			if (tmp == SUCCESS)
				return;
			std::thread t3 = std::thread(&phase_two_multithread_function, 3, 7, std::ref(min), std::ref(tmp), bebes, threshold, g_plusone, phase_2_heuristic, phase_two_goal, path);
			if (tmp == SUCCESS)
				return;
			t1.join();
			t2.join();
			t3.join();
		}
		path->pop();
		if(tmp == SUCCESS)
			return;
		threshold = tmp;
		i += 1;
	}
	std::cout << "\nFAILUUUURE\n";
}

