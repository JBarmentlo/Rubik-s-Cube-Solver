#include <iostream>
#include <stack>

#include "ida.hpp"
#include "heuristics.hpp"

using namespace std;

pair <int, stack<Node*>>		search(Node *current, int threshold, is_goal_function is_goal, stack<Node*> path, int (*heuristic)(CoordCube*))
{
	int		min;
	int		f;
	int		tmp;
	vector <Node*> bebes;

	current->set_h(heuristic(current->coordcube));
	f = current->f;
	path.push(current);
	if(is_goal(current->coordcube) == true)
		return {SUCCESS, path};
	if(f > threshold)
	{
		path.pop();
		return {f, path};
	}
	min = 2147483647;
	bebes = current->get_bebes();
	if(bebes.empty() == false)
	{
		for(auto bebe : bebes)
		{
			pair <int, stack<Node*>> test = search(bebe, threshold, is_goal, path, heuristic);
			tmp = test.first;
			path = test.second;
			if(tmp == SUCCESS)
				return {SUCCESS, path};
			if(tmp < min)
				min = tmp;
		}
	}
	path.pop();
	return {min, path};
}

bool		ida(Node *start, is_goal_function is_goal, int (*heuristic)(CoordCube*))
{
	stack<Node*>	path;
	int				i;
	int				threshold;
	int				tmp;

	i = 0;
	tmp = 0;
	start->set_h(heuristic(start->coordcube));
	threshold = start->f;
	while(i < MAX_ITER)
	{
		std::cout << "\n\n****\niter = " << i << "\n";
		std::cout << "threshold = " << threshold << "\n";
		pair <int, stack<Node*>> test = search(start, threshold, is_goal, path, heuristic);
		tmp = test.first;
		path = test.second;
		if(tmp == SUCCESS)
		{
			std::cout << "SUCCESSO: \n";
			std::cout << "path size = " << path.size() << "\n\n";
			return true;
		}
		threshold = tmp;
		i += 1;
	}
	std::cout << "FAILUUUURE\n";
	return false;
}


void		phase_one_solver(CoordCube cube)
{
	int min = INT32_MAX;
	int min_move;
	int h;
	cube.print();
	if (cube.corner_orientation_coord == 0 and cube.edge_orientation_coord == 0 and cube.UD_slice_coord == 0)
	{
		return;
	}

	for (int i = 0; i < N_MOVES; i++)
	{
		CoordCube bb = cube.create_baby_from_move_stack(i);
		h = phase_1_perfect_heuristic(bb);
		std::cout << "h " << h << std::endl;
		std::cout << min_move << std::endl;
		std::cout << min_move << std::endl;
		if (h < min)
		{
			min = h;
			min_move = i;
		}
	}
	std::cout << min_move << std::endl;
	std::cout << min_move << std::endl;

	phase_one_solver(cube.create_baby_from_move_stack(min));
}
