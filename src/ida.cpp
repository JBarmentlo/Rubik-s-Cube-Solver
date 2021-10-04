#include <iostream>
#include <stack>

#include "Node.hpp"

using namespace std;

#define MAX_ITER	100
#define SUCCESS		-1

pair <int, stack<Node*>>		search(Node *current, int threshold, int goal, stack<Node*> path)
{
	int		min;
	int		f;
	int		tmp;
	vector <Node*> bebes;

	f = current->f;
	path.push(current);
	cout << "\n\nEXPLORING: \n";
	current->print();
	// if(current->CoordCube == goal)
			// return {SUCCESS, path};
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
			pair <int, stack<Node*>> test = search(bebe, threshold, goal, path);
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


bool		ida(Node *start, int goal)
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
		pair <int, stack<Node*>> test = search(start, threshold, goal, path);
		tmp = test.first;
		path = test.second;
		if(tmp == SUCCESS)
		{
			std::cout << "SUCCESS: \n";
			return true;
		}
		threshold = tmp;
		i += 1;
	}
	std::cout << "FAILUUUURE\n";
	return false;
}

