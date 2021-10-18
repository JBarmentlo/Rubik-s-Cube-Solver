#ifndef SOLVER_HPP
#define SOLVER_HPP

#include "CoordCube.hpp"
#include "heuristics.hpp"
#include "utils.hpp"


#include <queue>


// typedef bool	(*is_goal_function)(CoordCube*);


void						phase_one_solver(CoordCube start, int steps, std::queue<int> *path);
void						phase_two_solver(CoordCube cube, std::queue<int> *path);
void						phase_two_solver_thread(CoordCube cube, std::queue<int> *path);
std::vector<CoordCube>		get_babies(CoordCube mommy_cube, g_function g_func, heuristic_function heuristic);


#endif