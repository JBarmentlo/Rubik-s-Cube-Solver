#include <iostream>
#include <stack>

#include "ida.hpp"


using namespace std;


bool corner_heuristic(CoordCube* coordcube)
{
	if (coordcube->corner_orientation_coord != 0)
		return (false);
	return (true);
}

pair <int, stack<Node*>>		search(Node *current, int threshold, is_goal_function is_goal, stack<Node*> path)
{
	int		min;
	int		f;
	int		tmp;
	vector <Node*> bebes;

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
			pair <int, stack<Node*>> test = search(bebe, threshold, is_goal, path);
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


bool		ida(Node *start, is_goal_function is_goal)
{
	stack<Node*>		path;
	int				i;
	int				threshold;
	int				tmp;

	i = 0;
	tmp = 0;
	threshold = start->f;
	while(i < MAX_ITER)
	{
		std::cout << "\n\n****\niter = " << i << "\n";
		std::cout << "threshold = " << threshold << "\n";
		pair <int, stack<Node*>> test = search(start, threshold, is_goal, path);
		tmp = test.first;
		path = test.second;
		if(tmp == SUCCESS)
		{
			std::cout << "SUCCESSO: \n";
			std::cout << "path size = " << path.size() << "\n\n";
			Node*	todelete;
			while (path.empty() == false)
			{
				todelete = path.top();
				std::cout << todelete->coordcube->corner_orientation_coord << std::endl;
				path.pop();
			}
			return true;
		}
		threshold = tmp;
		i += 1;
	}
	std::cout << "FAILUUUURE\n";
	return false;
}

