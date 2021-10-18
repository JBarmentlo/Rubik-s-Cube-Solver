#include "solver.hpp"
#include <thread>
#include <mutex>
#include <iostream>

typedef bool	(*is_goal_function)(CoordCube);

bool            phase_two_goal(CoordCube coordcube)
{
	if (coordcube.corner_permutation_coord_2 == 0 and
	coordcube.edge_permutation_coord_2 == 0 and
	coordcube.UD_slice_coord_2 == 0)
	{
		return true;
	}
	return false;
}



int		phase_2_search(CoordCube cube, int threshold, g_function g_func, heuristic_function heuristic, is_goal_function is_goal, std::queue<int> *path)
{
	int		min;
	int		tmp;

	int f = cube.f;
	path->push(cube.origin_move);
	if(is_goal(cube) == true)
		return (SUCCESS);
	if(f > threshold)
	{
		path->pop();
		return (f);
	}
	min = MAX_INT;
	std::vector<CoordCube> bebes = cube.get_babies_phase2(g_func, heuristic);
	if(bebes.empty() == false)
	{
		for(auto bebe : bebes)
		{
			tmp = phase_2_search(bebe, threshold, g_func, heuristic, is_goal, path);
			if(tmp == SUCCESS)
				return (SUCCESS);
			if(tmp < min)
				min = tmp;
		}
	}
	path->pop();
	return (min);
}

std::mutex lock;
void	phase_two_multithread_function(int start, int end, int &min, int &tmp, std::vector<CoordCube> bebes, int threshold, g_function g_func, heuristic_function heuristic, is_goal_function is_goal, std::queue<int> *path)
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

void	phase_two_multithread_function1(int start, int end, int *min, int *tmp, std::vector<CoordCube> bebes, int threshold, g_function g_func, heuristic_function heuristic, is_goal_function is_goal, std::queue<int> *path)
{
	for (int i = start; i < end; i++)
	{
		*tmp = phase_2_search(bebes[i], threshold, g_func, heuristic, is_goal, path);
		if(*tmp == SUCCESS)
			return; // SUCCESS
		if(*tmp < *min)
			*min = *tmp;
	}
	return;
}


void	phase_two_solver_thread(CoordCube cube, std::queue<int> *path)
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
			// phase_two_multithread_function1(0, 3, &min, &tmp, bebes, threshold, g_plusone, phase_2_heuristic, phase_two_goal, path);
			// if (tmp == SUCCESS)
			// 	return;
			// phase_two_multithread_function1(3, 7, &min, &tmp, bebes, threshold, g_plusone, phase_2_heuristic, phase_two_goal, path);
			// if (tmp == SUCCESS)
			// 	return;
			// phase_two_multithread_function1(7, 10, &min, &tmp, bebes, threshold, g_plusone, phase_2_heuristic, phase_two_goal, path);
			// if (tmp == SUCCESS)
			// 	return;
		}
		path->pop();
		if(tmp == SUCCESS)
		{
			std::cout << "\nSUCCESS FOR PHASE TWO\n";
			return;
		}
		threshold = tmp;
		i += 1;
	}
	std::cout << "\nFAILUUUURE\n";
}


void	phase_two_solver(CoordCube cube, std::queue<int> *path)
{
	int		i = 0;
	int		tmp = 0;
	int		threshold = THRESHOLD_INIT;

	cube.solver_init();
	while (i < MAX_ITER)
	{
		// std::cout << "threshold = " << threshold << std::endl;
		tmp = phase_2_search(cube, threshold, g_plusone, phase_2_heuristic, phase_two_goal, path);
		if(tmp == SUCCESS)
		{
			std::cout << "\nSUCCESS FOR PHASE TWO\n";
			return;
		}
		threshold = tmp;
		i += 1;
	}
	std::cout << "\nFAILUUUURE\n";
}




void		phase_one_solver(CoordCube cube, int steps, std::queue<int> *path)
{
	int min = MAX_INT;
	int min_move;
	int h;

	// std::cout << "coord: " << cube.flat_coord() <<"\th: " << phase_1_perfect_heuristic_seek(cube) <<  "                     " <<std::endl;
	if (cube.corner_orientation_coord_1 == 0 and cube.edge_orientation_coord_1 == 0 and cube.UD_slice_coord_1 == 0)
	{
		std::cout << "\nSUCCESS FOR PHASE ONE" << std::endl;
		return;
	}
	min_move = get_move_for_cube(cube);
	// std::cout << "move: " << min_move << std::endl;

	CoordCube next = cube.create_baby_from_move_phase1(min_move);
	path->push(min_move);
	phase_one_solver(next, steps + 1, path);
}
