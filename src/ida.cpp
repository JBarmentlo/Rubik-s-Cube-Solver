#include "ida.hpp"
#include "heuristics.hpp"

using namespace std;

int		search(Node *current, int threshold, is_goal_function is_goal, stack<Node*> *path, heuristic_function heuristic, g_function g_func, create_baby_function create_baby_from_move)
{
	int		min;
	int		f;
	int		tmp;
	vector <Node*> bebes;

	f = current->f;
	path->push(current);
	if(is_goal(current->coordcube) == true)
		return (SUCCESS);
	if(f > threshold)
	{
		path->pop();
		return (f);
	}
	min = 2147483647;
	bebes = current->get_bebes(g_func, heuristic, create_baby_from_move); // TODO add protection si heuristic a -1 donc erreur dans lecture du fichier
	if(bebes.empty() == false)
	{
		for(auto bebe : bebes)
		{
			tmp = search(bebe, threshold, is_goal, path, heuristic, g_func, create_baby_from_move);
			if(tmp == SUCCESS)
				return (SUCCESS);
			if(tmp < min)
				min = tmp;
		}
	}
	path->pop();
	return (min);
}


vector<int>		ida(Node *start, is_goal_function is_goal, heuristic_function heuristic, g_function g_func, create_baby_function create_baby_from_move)
{
	stack<Node*>	path;

	int				i;
	int				threshold;
	int				tmp;

	i = 0;
	tmp = 0;
	threshold = start->f;
	while(i < MAX_ITER)
	{
		std::cout << "threshold = " << threshold << "\n";
		tmp = search(start, threshold, is_goal, &path, heuristic, g_func, create_baby_from_move);
		if(tmp == SUCCESS)
		{
			std::cout << "\nSUCCESSO: \n";
			return (ordered_path(path));
		}
		threshold = tmp;
		i += 1;
	}
	std::cout << "\nFAILUUUURE\n";
	return (ordered_path(path));
}




void		phase_one_solver(CoordCube cube, int steps)
{
	int min = 123456;
	int min_move;
	int h;
	std::cout << "coord: " << cube.flat_coord() <<"\th: " << phase_1_perfect_heuristic_seek(cube) <<  "                     " <<std::endl;
	if (cube.corner_orientation_coord == 0 and cube.edge_orientation_coord == 0 and cube.UD_slice_coord == 0)
	{
		cube.print();
		return;
	}
	min_move = get_move_for_cube(cube);
	std::cout << "move: " << min_move << std::endl;

	std::cout << std::endl;
	std::cout << std::endl;
	CoordCube next = cube.create_baby_from_move_stack(min_move);
	phase_one_solver(next, steps + 1);
}
