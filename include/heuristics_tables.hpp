#ifndef HEURISTICS_TABLES_HPP
#define HEURISTICS_TABLES_HPP

#include "CoordCube.hpp"
#include "move_tables.hpp"
#include "utils.hpp"


#include <fstream>

typedef int**	(*reading_table_function)(void);

int*		    create_heuristics_table(int size, reading_table_function read);

// void            make_corner_ori_1_heuristics_table(void);
// void            make_edge_ori_1_heuristics_table(void);
// void            make_UD_slice_1_heuristics_table(void);
void            make_corner_perm_2_heuristics_table(void);
void            make_edge_perm_2_heuristics_table(void);
void            make_UD_2_heuristics_table(void);

void        	make_heuristics_tables_phase2(void);
void 			backwards_fill_h_table(int limit);
void			free_tables(void);


void 			testo(void);

#endif