#ifndef MOVE_TABLES_H
#define MOVE_TABLES_H

#include "cubiecube_utils.hpp"
#include "CubieCube.hpp"
#include <string.h>
#include <fstream>


typedef int 	(*get_coord_function)(cubiecube_t*);
typedef void 	(*set_coord_function)(int, cubiecube_t*);


void make_raw_move_table(get_coord_function get_coord, set_coord_function set_coord, int coord_max, std::string filename)
{
	cubiecube_t	cube;
	int			table[N_MOVES * (coord_max + 1)];
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
	out.write((char*)table, sizeof(int) * (N_MOVES * (coord_max + 1)));
}


#endif