#ifndef IDA_HPP
#define IDA_HPP

#include "Node.hpp"
#include "define.hpp"

typedef bool	(*is_goal_function)(CoordCube*);

typedef int**	(*reading_table_function)(void);



bool corner_heuristic(CoordCube* coordcube);

bool		ida(Node *start, is_goal_function is_goal);

bool		create_corner_heuristic_table(int size, reading_table_function read);


#endif