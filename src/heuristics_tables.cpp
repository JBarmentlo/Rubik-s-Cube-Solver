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
		if (new_coord != -1)
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



void    make_corner_ori_heuristics_table(void)
{
    int* corner_h_table = create_heuristics_table(N_CORNER_ORI, read_corner_orientation_move_table);

	std::ofstream out(CORNER_ORI_HEURISTIC_NAME, std::ios_base::binary);
	if (out.good() == true)
	{
		out.write((char*)corner_h_table, sizeof(int) * (N_CORNER_ORI));
		std::cout << "heuristic table created in: " << CORNER_ORI_HEURISTIC_NAME << " of size : " << N_CORNER_ORI << std::endl;
	}
	else
		std::cout << "PATH ERROR: can't create the following file" << CORNER_ORI_HEURISTIC_NAME << std::endl;
	
	free(corner_h_table);
}

void    make_edge_ori_heuristics_table(void)
{
	int* edge_h_table = create_heuristics_table(N_EDGE_ORI, read_edge_orientation_move_table);

	std::ofstream out(EDGE_ORI_HEURISTIC_NAME, std::ios_base::binary);
	if (out.good() == true)
	{
		out.write((char*)edge_h_table, sizeof(int) * (N_EDGE_ORI));
		std::cout << "heuristic table created in: " << EDGE_ORI_HEURISTIC_NAME << " of size : " << N_EDGE_ORI << std::endl;
	}
	else
		std::cout << "PATH ERROR: can't create the following file" << EDGE_ORI_HEURISTIC_NAME << std::endl;
	
	free(edge_h_table);
}

void    make_UD_slice1_heuristics_table(void)
{
    int* UD_slice_h_table = create_heuristics_table(N_UD, read_UD_move_table);

	std::ofstream out(UD_SLICE1_HEURISTIC_NAME, std::ios_base::binary);
	if (out.good() == true)
	{
		out.write((char*)UD_slice_h_table, sizeof(int) * (N_UD));
		std::cout << "heuristic table created in: " << UD_SLICE1_HEURISTIC_NAME << " of size : " << N_UD << std::endl;
	}
	else
		std::cout << "PATH ERROR: can't create the following file" << UD_SLICE1_HEURISTIC_NAME << std::endl;
		
	free(UD_slice_h_table);
}


void    make_corner_perm_heuristics_table(void)
{
    int* corner_perm_h_table = create_heuristics_table(N_CORNER_PERMUTATION, read_corner_permutation_move_table);

	std::ofstream out(CORNER_PERM_HEURISTIC_NAME, std::ios_base::binary);
	if (out.good() == true)
	{
		out.write((char*)corner_perm_h_table, sizeof(int) * (N_CORNER_PERMUTATION));
		std::cout << "heuristic table created in: " << CORNER_PERM_HEURISTIC_NAME << " of size : " << N_CORNER_PERMUTATION << std::endl;
	}
	else
		std::cout << "PATH ERROR: can't create the following file" << CORNER_PERM_HEURISTIC_NAME << std::endl;

	free(corner_perm_h_table);
}


void    make_edge_perm_heuristics_table(void)
{
    int* edge_perm_h_table = create_heuristics_table(N_EDGE_PERMUTATION_2, read_edge_permutation_move_table);

	std::ofstream out(EDGE_PERM_HEURISTIC_NAME, std::ios_base::binary);
	if (out.good() == true)
	{
		out.write((char*)edge_perm_h_table, sizeof(int) * (N_EDGE_PERMUTATION_2));
		std::cout << "heuristic table created in: " << EDGE_PERM_HEURISTIC_NAME  << " of size : " << N_EDGE_PERMUTATION_2 << std::endl;
	}
	else
		std::cout << "PATH ERROR: can't create the following file" << EDGE_PERM_HEURISTIC_NAME << std::endl;

	free(edge_perm_h_table);
}


void    make_UD_2_heuristics_table(void)
{
    int* UD_2_table = create_heuristics_table(N_UD_2, read_UD2_move_table);

	std::ofstream out(UD_SLICE2_HEURISTIC_NAME, std::ios_base::binary);
	if (out.good() == true)
	{
		out.write((char*)UD_2_table, sizeof(int) * (N_UD_2));
		std::cout << "heuristic table created in: " << UD_SLICE2_HEURISTIC_NAME  << " of size : " << N_UD_2 << std::endl;
	}
	else
		std::cout << "PATH ERROR: can't create the following file" << UD_SLICE2_HEURISTIC_NAME << std::endl;
	
	free(UD_2_table);
}

void	make_all_heuristics_tables(void)
{
	make_corner_ori_heuristics_table();
	make_edge_ori_heuristics_table();
	make_UD_slice1_heuristics_table();
	make_corner_perm_heuristics_table();
	make_edge_perm_heuristics_table(); // TODO: check for segfault!!
	make_UD_2_heuristics_table();
}