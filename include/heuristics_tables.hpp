#ifndef HEURISTICS_TABLES_HPP
#define HEURISTICS_TABLES_HPP

#include "move_tables.hpp"
#include <fstream>

typedef int**	(*reading_table_function)(void);

int*		    create_heuristics_table(int size, reading_table_function read);

void            make_corner_ori_heuristics_table(void);
void            make_edge_ori_heuristics_table(void);
void            make_UD_slice1_heuristics_table(void);
void            make_corner_perm_heuristics_table(void);
void            make_edge_perm_heuristics_table(void);
void            make_UD_2_heuristics_table(void);

void        	make_all_heuristics_tables(void);


#endif