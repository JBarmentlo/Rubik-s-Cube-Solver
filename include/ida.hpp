#ifndef IDA_HPP
#define IDA_HPP

#include "Node.hpp"
#include "define.hpp"
#include "move_tables.hpp"
#include "utils.hpp"
#include "ida_utils.hpp"
#include "CoordCube.hpp"

typedef bool	(*is_goal_function)(CoordCube*);



bool		ida(Node *start, is_goal_function is_goal, int (*heuristic)(CoordCube*));
void		phase_one_solver(CoordCube start);

#endif