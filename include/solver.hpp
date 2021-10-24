#ifndef SOLVER_HPP
#define SOLVER_HPP

#include "CoordCube.hpp"
#include "heuristics.hpp"
#include "utils.hpp"

#include <queue>
#include <stack>

typedef bool	(*is_goal_function)(CoordCube);


bool            			phase_one_goal(CoordCube coordcube);
bool            			phase_two_goal(CoordCube coordcube);
int							phase_2_search(CoordCube cube, int threshold, g_function g_func, heuristic_function heuristic, is_goal_function is_goal, std::stack<int> *path);
void						phase_one_solver(CoordCube start, int steps, std::queue<int> *path);
void						phase_two_solver(CoordCube cube, std::stack<int> *path);
std::vector<CoordCube>		get_babies(CoordCube mommy_cube, g_function g_func, heuristic_function heuristic);


#endif