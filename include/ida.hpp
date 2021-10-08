#ifndef IDA_HPP
#define IDA_HPP

#include "Node.hpp"
#include "define.hpp"
#include "move_tables.hpp"
#include "utils.hpp"
#include "ida_utils.hpp"
#include "CoordCube.hpp"

#include <iostream>
#include <stack>


typedef bool	(*is_goal_function)(CoordCube*);


void			phase_one_solver(CoordCube start, int steps);
vector<int>		ida(Node *start, is_goal_function is_goal, heuristic_function heuristic, g_function g_func, create_baby_function create_baby_from_move);


#endif