#include "move_tables.hpp"

void 		make_raw_move_table(get_coord_function get_coord, set_coord_function set_coord, int coord_max, std::string filename)
{
	cubiecube_t	cube;
	int			table[N_MOVES * (coord_max)];
	memcpy(&cube, &homecube, sizeof(cube));
	cubiecube_t* moves = get_moves();

	for (int i = 0; i < coord_max; i++)
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

// void make_all_move_tables(void)
// {
// 	for (int i = 0; i < N_TABLES; i++)
// 	{
// 		std::cout << "Making " << table_file_names[i] << "of size: " << coord_range[i] << std::endl;
// 		make_raw_move_table(coord_getters[i], coord_setters[i], coord_range[i], table_file_names[i]);
// 		std::cout << "Done" << std::endl;
// 	}
// }

int** 		read_raw_move_table(int coord_max, std::string filename)
{
	int*			table;
	table = (int*)malloc(N_MOVES * (coord_max) * sizeof(int));
	int**			pretty_table;
	pretty_table = (int**)malloc((coord_max) * sizeof(int*));

	std::ifstream in(filename, std::ios_base::binary);
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
		
		make_raw_move_table(coord_getters[i], coord_setters[i], coord_range[i], table_file_names[i]);
		std::cout << "Done" << std::endl;
	}
}