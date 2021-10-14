#include "ida.hpp"

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



// using namespace std;

// int		search(Node *current, int threshold, is_goal_function is_goal, stack<Node*> *path, heuristic_function heuristic, g_function g_func, create_baby_function create_baby_from_move)
// {
// 	int		min;
// 	int		f;
// 	int		tmp;
// 	vector <Node*> bebes;

// 	f = current->f;
// 	path->push(current);
// 	if(is_goal(current->coordcube) == true)
// 		return (SUCCESS);
// 	if(f > threshold)
// 	{
// 		path->pop();
// 		return (f);
// 	}
// 	min = 2147483647;
// 	bebes = current->get_bebes(g_func, heuristic, create_baby_from_move); // TODO add protection si heuristic a -1 donc erreur dans lecture du fichier
// 	if(bebes.empty() == false)
// 	{
// 		for(auto bebe : bebes)
// 		{
// 			tmp = search(bebe, threshold, is_goal, path, heuristic, g_func, create_baby_from_move);
// 			if(tmp == SUCCESS)
// 				return (SUCCESS);
// 			if(tmp < min)
// 				min = tmp;
// 		}
// 	}
// 	path->pop();
// 	return (min);
// }


// vector<int>		ida(Node *start, is_goal_function is_goal, heuristic_function heuristic, g_function g_func, create_baby_function create_baby_from_move)
// {
// 	stack<Node*>	path;

// 	int				i;
// 	int				threshold;
// 	int				tmp;

// 	i = 0;
// 	tmp = 0;
// 	threshold = start->f;
// 	while(i < MAX_ITER)
// 	{
// 		std::cout << "threshold = " << threshold << "\n";
// 		tmp = search(start, threshold, is_goal, &path, heuristic, g_func, create_baby_from_move);
// 		if(tmp == SUCCESS)
// 		{
// 			std::cout << "\nSUCCESSO: \n";
// 			return (ordered_path(path));
// 		}
// 		threshold = tmp;
// 		i += 1;
// 	}
// 	std::cout << "\nFAILUUUURE\n";
// 	return (ordered_path(path));
// }

bool	f_sorting(CoordCube one, CoordCube two)
{
	return (one.f < two.f);
}

bool  is_allowed_move_phase2(int move)
{
  if (is_allowed_quarter_turns[move % N_BASIC_MOVES] == false &&
      move != ((move % N_BASIC_MOVES) + N_BASIC_MOVES))
      return false;
    return true;
}

std::vector<CoordCube>    get_babies(CoordCube mommy_cube, g_function g_func, heuristic_function heuristic)
{
    std::vector<CoordCube>   bebes(N_MOVES);
    CoordCube      		baby_coordcube;
    int             	nb_of_moves = 0;

    for (int move = 0; move < N_MOVES; move++)
    {
        if (((mommy_cube.origin_move == NO_MOVE_APPLIED) or (move % N_BASIC_MOVES) != (mommy_cube.origin_move % N_BASIC_MOVES)) && is_allowed_move_phase2(move))
        {
            baby_coordcube = create_baby_from_move_phase2(mommy_cube, move);
			baby_coordcube.g = g_func(mommy_cube.g);
			baby_coordcube.h = heuristic(baby_coordcube);
			baby_coordcube.f = baby_coordcube.g + baby_coordcube.h;
			bebes[nb_of_moves] = baby_coordcube;
			nb_of_moves += 1;
        }
    }
    bebes.resize(nb_of_moves);
    std::sort (bebes.begin(), bebes.end(), f_sorting);
    return (bebes);
}

int		search_2(CoordCube cube, int threshold, g_function g_func, heuristic_function heuristic, is_goal_function is_goal, std::queue<int> *path)
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
	std::vector<CoordCube> bebes = get_babies(cube, g_func, heuristic);
	if(bebes.empty() == false)
	{
		for(auto bebe : bebes)
		{
			tmp = search_2(bebe, threshold, g_func, heuristic, is_goal, path);
			if(tmp == SUCCESS)
				return (SUCCESS);
			if(tmp < min)
				min = tmp;
		}
	}
	path->pop();
	return (min);
}


void	phase_two_solver(CoordCube cube, int threshold, std::queue<int> *path)
{
	int		i = 0;
	int		tmp = 0;

	cube.g = 0;
	cube.h = 0;
	cube.f = 0;
	cube.origin_move = NO_MOVE_APPLIED;
	while (i < MAX_ITER)
	{
		std::cout << "threshold = " << threshold << std::endl;
		tmp = search_2(cube, threshold, g_plusone, phase_2_heuristic, phase_two_goal, path);
		
		if(tmp == SUCCESS)
		{
			std::cout << "\nSUCCESSO: \n";
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
