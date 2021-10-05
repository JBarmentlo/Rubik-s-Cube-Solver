#include "heuristics_tables.hpp"

void	walk(int coord, int steps, int** moves_table, int* heuristics_table, int size)
{
	int new_coord;

	if (heuristics_table[coord] != -1 and heuristics_table[coord] <= steps)
	{
		return;
	}
	
	heuristics_table[coord] = steps;
	for (int move = 0; move < N_MOVES; move++)
	{
		new_coord = moves_table[coord][move];
		walk(new_coord, steps + 1, moves_table, heuristics_table, size);
	}
	return;
}


int*		create_heuristics_table(int size, reading_table_function read)
{
	int** moves_table = read();

	int* heuristics_table = (int*)malloc(sizeof(int) * size);

	fill_table_with_value(heuristics_table, -1, size);

	walk(0, 0, moves_table, heuristics_table, size);
	
	return heuristics_table;
}




void    make_corner_heuristics_table(void)
{
    int* corner_h_table = create_heuristics_table(N_CORNER_ORI, read_corner_orientation_move_table);

	std::ofstream out(CORNER_ORI_HEURISTIC_NAME, std::ios_base::binary);
	out.write((char*)corner_h_table, sizeof(int) * (N_CORNER_ORI));
	
	free(corner_h_table);
}

void    make_edge_heuristics_table(void)
{
	int* edge_h_table = create_heuristics_table(N_EDGE_ORI, read_edge_orientation_move_table);

	std::ofstream out(EDGE_ORI_HEURISTIC_NAME, std::ios_base::binary);
	out.write((char*)edge_h_table, sizeof(int) * (N_EDGE_ORI));
	
	free(edge_h_table);
}

void    make_UD_slice_heuristics_table(void)
{
    int* UD_slice_h_table = create_heuristics_table(N_UD, read_UD_move_table);

	std::ofstream out(UD_SLICE_HEURISTIC_NAME, std::ios_base::binary);
	out.write((char*)UD_slice_h_table, sizeof(int) * (N_UD));
	
	free(UD_slice_h_table);
}