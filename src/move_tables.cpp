#include "move_tables.hpp"
#include <string.h>
#include <fstream>


void 		make_raw_move_table(get_coord_function get_coord, set_coord_function set_coord, int coord_max, std::string filename, int edges_corners, int phase)
{
	cubiecube_t	cube;
	int			table[N_MOVES * (coord_max)];
	memcpy(&cube, &homecube, sizeof(cube));
	cubiecube_t* moves = get_moves();

	for (int i = 0; i < coord_max; i++)
	{
		// if (i % 10000 == 0 and i != 0)
		// {
		// 	std::cout << i << " " << std::endl;
		// }
		// std::cout <<  "set " << i << std::endl;
		set_coord(i, &cube);
		for (int j = 0; j < N_BASIC_MOVES; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				apply_move(&cube, &moves[j]);
				if (phase == 1 or k == 1 or is_allowed_quarter_turns[j])
				{
					table[N_MOVES * i + j + 6 * k] = get_coord(&cube);
				}
				else
				{
					table[N_MOVES * i + j + 6 * k] = -1; //TODO: check if necesary
				}
				if (table[N_MOVES * i + j + 6 * k] >= coord_max)
				{
					std::cout << "THIS SHOULD NEVER PRINT" << std::endl;
				}
			}
			apply_move(&cube, &moves[j]);
		}
	}
	std::ofstream out(filename, std::ios_base::binary);
	if (out.good() == true)
		out.write((char*)table, sizeof(int) * (N_MOVES * (coord_max)));
	else
		std::cout << "PATH ERROR: cannot create the following file: " << filename << std::endl;
}

int** 		read_raw_move_table(int coord_max, std::string filename)
{
	int*			table;
	table = (int*)malloc(N_MOVES * (coord_max) * sizeof(int));
	int**			pretty_table;
	pretty_table = (int**)malloc((coord_max) * sizeof(int*));

	std::ifstream in(filename, std::ios_base::binary);
	if (in.good() == false)
	{
		std::cout << "PATH ERROR: cannot read the following file: " << filename << std::endl;
		return (nullptr);
	}
	in.read((char*)table, N_MOVES * (coord_max) * sizeof(int));

	for (int i = 0; i < coord_max; i++)
	{
		pretty_table[i] = &table[i * N_MOVES];
	}
	return pretty_table;
}

int**		read_corner_orientation_move_table()
{
	return (read_raw_move_table(N_CORNER_ORI, CORNER_ORI_NAME));
}

int**		read_corner_permutation_move_table()
{
	return (read_raw_move_table(N_CORNER_PERMUTATION, CORNER_PERMUTATION_NAME));
}


int**		read_edge_orientation_move_table()
{
	return (read_raw_move_table(N_EDGE_ORI, EDGE_ORI_NAME));
}

int**		read_edge_permutation_move_table()
{
	return (read_raw_move_table(N_EDGE_PERMUTATION_2, EDGE_PERMUTATION_2_NAME));
}


int**		read_UD_move_table()
{
	return (read_raw_move_table(N_UD, UD_SLICE_NAME));
}


int**		read_UD2_move_table()
{
	return (read_raw_move_table(N_UD_2, UD_2_NAME));
}


int** 		read_raw_move_table_phase_2(int coord_max, std::string filename)
{
	int*			table;
	table = (int*)malloc(N_MOVES * (coord_max) * sizeof(int));
	int**			pretty_table;
	pretty_table = (int**)malloc((coord_max) * sizeof(int*));

	std::ifstream in(filename, std::ios_base::binary);
	in.read((char*)table, N_MOVES * (coord_max ) * sizeof(int));

	for (int i = 0; i < coord_max + 1; i++)
	{
		pretty_table[i] = &table[i * N_MOVES];
	}
	return pretty_table;
}

void 		make_all_move_tables(void)
{
	for (int i = 0; i < N_TABLES; i++)
	{
		std::cout << "Making " << table_file_names[i] << " of size: " << coord_range[i] << std::endl;
		make_raw_move_table(coord_getters[i], coord_setters[i], coord_range[i], table_file_names[i], edge_corner_moves[i], phase[i]);
		std::cout << "Done" << std::endl;
	}
}
