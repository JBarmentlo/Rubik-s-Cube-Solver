#ifndef IDA_UTILS_HPP
#define IDA_UTILS_HPP

#include "CoordCube.hpp"

typedef bool	(*is_goal_function)(CoordCube*);

bool corner_heuristic(CoordCube* coordcube);

#endif