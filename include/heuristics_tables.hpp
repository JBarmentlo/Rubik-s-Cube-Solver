#ifndef HEURISTICS_TABLES_HPP
#define HEURISTICS_TABLES_HPP

#include "move_tables.hpp"
#include <fstream>

typedef int**	(*reading_table_function)(void);

int*		create_heuristics_table(int size, reading_table_function read);


void    	make_corner_heuristics_table(void);
void    	make_edge_heuristics_table(void);
void    	make_UD_slice_heuristics_table(void);
void    	make_perfect_heuristics_table(void);
void	    make_perfect_heuristics_table_iterative(int limit);


#endif