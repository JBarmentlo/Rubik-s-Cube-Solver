#ifndef SOLVER_HPP
#define SOLVER_HPP

#include "CoordCube.hpp"
#include "heuristics.hpp"
#include "heuristics.hpp"
#include "utils.hpp"


#include <queue>
#include <algorithm>



// typedef bool	(*is_goal_function)(CoordCube*);


void						phase_one_solver(CoordCube start, int steps, std::queue<int> *path);
void						phase_two_solver(CoordCube cube, std::queue<int> *path);
std::vector<CoordCube>		get_babies(CoordCube mommy_cube, g_function g_func, heuristic_function heuristic);


// vector<int>		ida(Node *start, is_goal_function is_goal, heuristic_function heuristic, g_function g_func, create_baby_function create_baby_from_move);


#endif