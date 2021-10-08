#ifndef IDA_UTILS_HPP
#define IDA_UTILS_HPP

#include "CoordCube.hpp"
#include "Node.hpp"
#include <vector>
#include <stack>

typedef bool	(*is_goal_function)(CoordCube*);

bool            phase_one_goal(CoordCube* coordcube);

bool            phase_two_goal(CoordCube* coordcube);


bool            corner_heuristic(CoordCube* coordcube);

vector<int>		ordered_path(stack<Node*> ida_path);

void            print_path(vector<int> path);


#endif