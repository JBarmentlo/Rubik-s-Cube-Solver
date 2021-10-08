#ifndef MOVE_TABLES_H
#define MOVE_TABLES_H

#include "cubiecube_utils.hpp"
#include "CubieCube.hpp"
#include "define.hpp"
#include <string.h>
#include <fstream>


typedef int 	(*get_coord_function)(cubiecube_t*);
typedef void 	(*set_coord_function)(int, cubiecube_t*);

#define 	N_TABLES 		6
#define  	EDGES_ONLY 		1
#define  	CORNERS_ONLY 	2
#define  	BOTH		 	3


static get_coord_function 	coord_getters[N_TABLES] 	= {corner_orientation_coordinate,	edge_orientation_coordinate, 	corner_permutation_coordinate,		UD_slice_coordinate, 	edge_permutation_coordinate_2, 		UD_slice_sorted_coordinate_2};
static set_coord_function 	coord_setters[N_TABLES] 	= {set_corner_orientation_coord,	set_edge_orientation_coord, 	set_corner_permutation_coordinate, 	set_UD_slice_coord, 	set_edge_permutation_coordinate_2, 	set_UD_slice_sorted_coordinate_2};
static std::string			table_file_names[N_TABLES] 	= {CORNER_ORI_NAME,					EDGE_ORI_NAME, 					CORNER_PERMUTATION_NAME,			UD_SLICE_NAME, 			EDGE_PERMUTATION_2_NAME, 			UD_2_NAME};
static int					coord_range[N_TABLES] 		= {N_CORNER_ORI,					N_EDGE_ORI, 					N_CORNER_PERMUTATION,				N_UD, 					N_EDGE_PERMUTATION_2, 				N_UD_2};
static int					edge_corner_moves[N_TABLES] = {CORNERS_ONLY, 					EDGES_ONLY, 					CORNERS_ONLY,						EDGES_ONLY, 			EDGES_ONLY, 						EDGES_ONLY};
static int					phase[N_TABLES] 			= {1, 								1, 								2,									1, 						2, 									2};


void 		make_raw_move_table(get_coord_function get_coord, set_coord_function set_coord, int coord_max, std::string filename, int edge_corners_moves, int phase);

void 		make_all_move_tables(void);

int** 		read_raw_move_table(int coord_max, std::string filename);
int**		read_corner_orientation_move_table();
int**		read_edge_orientation_move_table();
int**		read_UD_move_table();
int**		read_corner_permutation_move_table();
int**		read_edge_permutation_move_table();
int**		read_UD2_move_table();

int** 		read_raw_move_table_phase_2(int coord_max, std::string filename);


#endif