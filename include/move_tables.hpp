#ifndef MOVE_TABLES_H
#define MOVE_TABLES_H

#include "cubiecube_utils.hpp"
#include "CubieCube.hpp"
#include "define.hpp"
#include <string.h>
#include <fstream>


typedef int 	(*get_coord_function)(cubiecube_t*);
typedef void 	(*set_coord_function)(int, cubiecube_t*);

#define N_TABLES 6
static get_coord_function 	coord_getters[N_TABLES] 	= {corner_orientation_coordinate, edge_orientation_coordinate, corner_permutation_coordinate, UD_slice_coordinate, edge_permutation_coordinate_2, UD_slice_sorted_coordinate_2};
static set_coord_function 	coord_setters[N_TABLES] 	= {set_corner_orientation_coord, set_edge_orientation_coord, set_corner_permutation_coordinate, set_UD_slice_coord, set_edge_permutation_coordinate_2, set_UD_slice_sorted_coordinate_2};
static std::string			table_file_names[N_TABLES] 	= {CORNER_ORI_NAME, EDGE_ORI_NAME, CORNER_PERMUTATION_NAME, UD_SLICE_NAME, EDGE_PERMUTATION_2_NAME, UD_2_NAME};
static int					coord_range[N_TABLES] 		= {N_CORNER_ORI, N_EDGE_ORI, N_CORNER_PERMUTATION, N_UD, N_EDGE_PERMUTATION_2, N_UD_2};



void 		make_raw_move_table(get_coord_function get_coord, set_coord_function set_coord, int coord_max, std::string filename)
{
	cubiecube_t	cube;
	int			table[N_MOVES * (coord_max)];
	memcpy(&cube, &homecube, sizeof(cube));
	cubiecube_t* moves = get_moves();

	for (int i = 0; i <= coord_max; i++)
	{
		set_coord(i, &cube);
		for (int j = 0; j < N_BASIC_MOVES; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				apply_move(&cube, &moves[j]);
				table[N_MOVES * i + j + 6 * k] = get_coord(&cube);
			}
			apply_move(&cube, &moves[j]);
		}
	}
	std::ofstream out(filename, std::ios_base::binary);
	out.write((char*)table, sizeof(int) * (N_MOVES * (coord_max)));
}

void make_all_move_tables(void)
{
	for (int i = 0; i < N_TABLES; i++)
	{
		std::cout << "Making " << table_file_names[i] << "of size: " << coord_range[i] << std::endl;
		make_raw_move_table(coord_getters[i], coord_setters[i], coord_range[i], table_file_names[i]);
		std::cout << "Done" << std::endl;
	}
}

int** 		read_raw_move_table(int coord_max, std::string filename)
{
	int*			table;
	table = (int*)malloc(N_MOVES * (coord_max + 1) * sizeof(int));
	int**			pretty_table;
	pretty_table = (int**)malloc((coord_max + 1) * sizeof(int*));

	std::ifstream in(filename, std::ios_base::binary);
	in.read((char*)table, N_MOVES * (coord_max + 1) * sizeof(int));

	for (int i = 0; i < coord_max + 1; i++)
	{
		pretty_table[i] = &table[i * N_MOVES];
	}
	return pretty_table;
}

int**		read_corner_orientation_move_table()
{
	return (read_raw_move_table(N_CORNER_ORI, CORNER_ORI_NAME));
}

int**		read_edge_orientation_move_table()
{
	return (read_raw_move_table(N_EDGE_ORI, EDGE_ORI_NAME));
}

int**		read_UD_move_table()
{
	return (read_raw_move_table(N_UD, UD_SLICE_NAME));
}

int** 		read_raw_move_table_phase_2(int coord_max, std::string filename)
{
	int*			table;
	table = (int*)malloc(N_MOVES * (coord_max + 1) * sizeof(int));
	int**			pretty_table;
	pretty_table = (int**)malloc((coord_max + 1) * sizeof(int*));

	std::ifstream in(filename, std::ios_base::binary);
	in.read((char*)table, N_MOVES * (coord_max + 1) * sizeof(int));

	for (int i = 0; i < coord_max + 1; i++)
	{
		pretty_table[i] = &table[i * N_MOVES];
	}
	return pretty_table;
}


#endif