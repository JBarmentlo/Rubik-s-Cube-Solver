#ifndef IDA_HPP
#define IDA_HPP

#include "Node.hpp"
#include "define.hpp"

typedef bool	(*is_goal_function)(CoordCube*);


bool corner_heuristic(CoordCube* coordcube);

bool		ida(Node *start, is_goal_function is_goal);


#endif