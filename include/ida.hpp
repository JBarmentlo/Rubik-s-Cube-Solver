#ifndef IDA_HPP
#define IDA_HPP

#include "Node.hpp"
#include "define.hpp"
#include "move_tables.hpp"
#include "utils.hpp"
#include "ida_utils.hpp"

typedef bool	(*is_goal_function)(CoordCube*);

typedef int**	(*reading_table_function)(void);



// bool corner_heuristic(CoordCube* coordcube);

bool		ida(Node *start, is_goal_function is_goal);

int*		create_heuristics_table(int size, reading_table_function read);


#endif