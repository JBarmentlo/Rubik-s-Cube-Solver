#include "solver.hpp"

bool            phase_one_goal(CoordCube coordcube)
{
	if (coordcube.corner_orientation_coord_1 == 0 and
	coordcube.edge_orientation_coord_1 == 0 and
	coordcube.UD_slice_coord_1 == 0)
	{
		return true;
	}
	return false;
}


bool            phase_two_goal(CoordCube coordcube)
{
	if (coordcube.corner_permutation_coord_2 == 0 and
	coordcube.edge_permutation_coord_2 == 0 and
	coordcube.UD_slice_coord_2 == 0)
		return true;
	return false;
}



int		phase_2_search(CoordCube cube, int threshold, g_function g_func, heuristic_function heuristic, is_goal_function is_goal, std::stack<int> *path)
{
	int		min;
	int		tmp;

	int f = cube.f;
	if(is_goal(cube) == true)
		return (SUCCESS);
	if(f > threshold)
		return (f);
	min = MAX_INT;
	std::vector<CoordCube> bebes = cube.get_babies_phase2(g_func, heuristic);
	if(bebes.empty() == false)
	{
		for(auto bebe : bebes)
		{
			tmp = phase_2_search(bebe, threshold, g_func, heuristic, is_goal, path);
			if(tmp == SUCCESS)
			{
				path->push(bebe.origin_move);
				return (SUCCESS);
			}
			if(tmp < min)
				min = tmp;
		}
	}
	return (min);
}


void	phase_two_solver(CoordCube cube, std::stack<int> *path)
{
	int		i = 0;
	int		tmp = 0;
	int		threshold = THRESHOLD_INIT;

	cube.solver_init();
	while (i < MAX_ITER)
	{
		tmp = phase_2_search(cube, threshold, g_plusone, phase_2_heuristic, phase_two_goal, path);
		if(tmp == SUCCESS)
			return;
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
		return;
	min_move = get_move_for_cube(cube);
	// std::cout << "move: " << min_move << std::endl;

	CoordCube next = cube.create_baby_from_move_phase1(min_move);
	path->push(min_move);
	phase_one_solver(next, steps + 1, path);
}
