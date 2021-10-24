#ifndef DEYA_HPP
#define	DEYA_HPP

typedef bool	(*is_goal_function)(CoordCube);


#include <vector>

void	test_result(std::vector<int> input_shuffle, std::vector<int> output_shuffle, int phase_one_length);
void	test_first_steps(std::vector<int> input_shuffle);
void	test_after_phase_one(CoordCube coordie1, cubiecube_t cubie1);
void	phase_two_solver_test(CoordCube cube, std::stack<int> *path);
int		phase_2_search_test(CoordCube cube, int threshold, g_function g_func, heuristic_function heuristic, is_goal_function is_goal, std::stack<int> *path);






#endif