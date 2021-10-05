#ifndef MOVE_TABLES_H
#define MOVE_TABLES_H

#include "cubiecube_utils.hpp"
#include "CubieCube.hpp"
#include <string.h>
#include <fstream>


typedef int 	(*get_coord_function)(cubiecube_t*);
typedef void 	(*set_coord_function)(int, cubiecube_t*);


void 		make_raw_move_table(get_coord_function get_coord, set_coord_function set_coord, int coord_max, std::string filename);


int** 		read_raw_move_table(int coord_max, std::string filename);

int**		read_corner_orientation_move_table();

int**		read_edge_orientation_move_table();

int**		read_UD_move_table();

int** 		read_raw_move_table_phase_2(int coord_max, std::string filename);


#endif