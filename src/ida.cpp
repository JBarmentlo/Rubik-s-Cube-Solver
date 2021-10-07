#include <iostream>
#include <stack>

#include "ida.hpp"

using namespace std;

pair <int, stack<Node*>>		search(Node *current, int threshold, is_goal_function is_goal, stack<Node*> path, heuristic_function heuristic, g_function g_func)
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
	bebes = current->get_bebes(g_func, heuristic); // TODO add protection si heuristic a -1 donc erreur dans lecture du fichier
	if(bebes.empty() == false)
	{
		for(auto bebe : bebes)
		{
			pair <int, stack<Node*>> ret = search(bebe, threshold, is_goal, path, heuristic, g_func);
			tmp = ret.first;
			path = ret.second;
			if(tmp == SUCCESS)
				return {SUCCESS, path};
			if(tmp < min)
				min = tmp;
		}
	}
	path.pop();
	return {min, path};
}


bool		ida(Node *start, is_goal_function is_goal, heuristic_function heuristic, g_function g_func)
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
		std::cout << "\n\n****\niter = " << i << "\n";
		std::cout << "threshold = " << threshold << "\n";
		pair <int, stack<Node*>> ret = search(start, threshold, is_goal, path, heuristic, g_func);
		tmp = ret.first;
		path = ret.second;
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


