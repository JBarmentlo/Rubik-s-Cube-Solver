#include "heuristics_tables.hpp"
#include "CoordCube.hpp"
#include "utils.hpp"


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


int*	create_heuristics_table(int size, reading_table_function read)
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

#define UNFILLED 15

void	walk_3(CoordCube coord, unsigned char steps, unsigned char* heuristics_table, int limit, int mommy_move)
{
	const unsigned int flat_coord = coord.flat_coord();
	// static unsigned int i = 0;

	if (steps > limit)
	{
		return;
	}

	unsigned char val = read_half_char_table(heuristics_table, flat_coord);
	if (val != (unsigned char)UNFILLED and val < (unsigned char)steps)
	{
		return;
	}
	if (val == (unsigned char)UNFILLED)
	{
		// i = i + 1;
		// if (i % 1048576 == 0)
		// {
		// 	std::cout << "filled " << i << " / " << N_EDGE_ORI * N_CORNER_ORI * N_UD <<std::endl;
		// }
		write_half_char_table(heuristics_table, steps, flat_coord);
	}
	else if (val > (unsigned char)steps)
	{
		write_half_char_table(heuristics_table, steps, flat_coord);
	}

	for (int move = 0; move < N_MOVES; move++)
	{
		// if (steps == 0  or (move % 6 != mommy_move % 6))
		// {
		// 	CoordCube bb_cube = coord.create_baby_from_move_stack(move);
		// 	walk_3(bb_cube, steps + 1, heuristics_table, limit, move);
		// }
		CoordCube bb_cube = coord.create_baby_from_move_stack(move);
		walk_3(bb_cube, steps + 1, heuristics_table, limit, move);
	}
	return;
}

int		reverse_walk(CoordCube coord, int steps, int current_min, unsigned char* heuristics_table, int limit, int mommy_move)
{
	static int written = 0;
	int coord_val = read_half_char_table(heuristics_table, coord.flat_coord());
	current_min = std::min(coord_val, current_min);

	if (coord_val >= current_min)
		return (current_min + 1);


	if (steps >= limit)
		return (coord_val + 1);

	if (coord_val > current_min)
	{
		written += 1;
		write_half_char_table(heuristics_table, current_min, coord.flat_coord());
		if (written >> 15 != 0)
			std::cout << "filled " <<  written << " / " << N_EDGE_ORI * N_CORNER_ORI * (float)N_UD <<std::endl;
	}

	for (int move = 0; move < N_MOVES; move++)
	{
		if (steps == 0  or (move % 6 != mommy_move % 6))
		{
			CoordCube bb_cube = coord.create_baby_from_move_stack(move);
			current_min = std::min(current_min, reverse_walk(bb_cube, steps + 1,  current_min - 1, heuristics_table, limit, move));
		}
	}
	if (coord_val > current_min)
	{
		written += 1;
		write_half_char_table(heuristics_table, current_min, coord.flat_coord());
		if (written % 1024 == 0)
			std::cout << "filled " <<  written << " / " << N_EDGE_ORI * N_CORNER_ORI * N_UD <<std::endl;
	}
	return (current_min + 1);
}


void    make_perfect_heuristics_table(void)
{
	unsigned char* perfect_h_table = (unsigned char*)malloc(sizeof(char) * N_EDGE_ORI / 2 * N_CORNER_ORI * N_UD);
	fill_half_char_table(perfect_h_table, UNFILLED, N_EDGE_ORI * N_UD * N_CORNER_ORI);
	// for (unsigned int i = 0; i < N_EDGE_ORI / 2 * N_CORNER_ORI * N_UD; i++)
	// {
	// 	write_half_char_table(perfect_h_table, 13, i);
	// 	// std::cout << read_half_char_table(perfect_h_table, i) << std::endl;
	// }
	std::cout << "walk" << std::endl;
	for (int i = 12; i < 13; i++)
	{
		std::cout << i << std::endl;
		std::cout << std::endl;
		walk_3(CoordCube(0), 0, perfect_h_table, i, 0);
	}
	std::cout << "FIlling %: " << get_table_filling(perfect_h_table) << std::endl;
	// std::cout << "\n\nreverse walk REVEERSE \n\n" << std::endl;
	// for (unsigned int i = 0; i < N_EDGE_ORI * N_CORNER_ORI * N_UD; i++)
	// {
	// 	if (i % (N_EDGE_ORI / 16 * N_CORNER_ORI * N_UD) == 0)
	// 	{
	// 		std::cout << "coord " << i / (N_EDGE_ORI / 16 * N_CORNER_ORI * N_UD) << std::endl;
	// 	}
	// 	if (read_half_char_table(perfect_h_table, i) == UNFILLED)
	// 		reverse_walk(CoordCube(i), 0, UNFILLED + 1, perfect_h_table, 3, 0);
	// }
	
	std::cout << "done walk" << std::endl;
	std::ofstream out(PHASE_ONE_HEURISTIC_NAME, std::ios_base::binary);
	out.write((char*)perfect_h_table, sizeof(char) * N_EDGE_ORI / 2 * N_CORNER_ORI * N_UD);
	
	free(perfect_h_table);
}

void    make_perfect_heuristics_table_iterative(int limit)
{
	unsigned char* perfect_h_table = (unsigned char*)malloc(sizeof(char) * N_EDGE_ORI / 2 * N_CORNER_ORI * N_UD);
	fill_half_char_table(perfect_h_table, UNFILLED, N_EDGE_ORI * N_UD * N_CORNER_ORI);
	std::cout << "walk" << std::endl;
	write_half_char_table(perfect_h_table, 0, 0);
	for (unsigned int i = 0; i < limit; i++) // TODO 7 CHANGE TO 12 / 13
	{
		std::cout << "i " << i << std::endl;
		for (unsigned int coord = 0; coord < N_EDGE_ORI * N_UD * N_CORNER_ORI; coord++)
		{
			if (coord % (N_EDGE_ORI / 16 * N_CORNER_ORI * N_UD) == 0)
			{
				std::cout << "filling " << get_table_filling(perfect_h_table) << std::endl;
			}
			unsigned char val = read_half_char_table(perfect_h_table, coord);
			if (val == i)
				walk_3(CoordCube(coord), val, perfect_h_table, val + 1, 0);
		}
		std::cout <<  std::endl;
		std::cout <<  std::endl;

	}
	
	// for (unsigned int i = 0; i < 1000; i++)
	// {
	// 	if (read_half_char_table(perfect_h_table, i) == (unsigned char)UNFILLED)
	// 	{
	// 		std::cout << "err " << (int)read_half_char_table(perfect_h_table, i) <<  std::endl;
	// 	}
	// }
	// for (unsigned int i = 0; i < 1000; i++)
	// {
	// 	std::cout << (int)read_half_char_table(perfect_h_table, i) <<  std::endl;
	// }
	std::cout << "done walk" << std::endl;
	std::ofstream out(PHASE_ONE_HEURISTIC_NAME, std::ios_base::binary);
	out.write((char*)perfect_h_table, sizeof(char) * N_EDGE_ORI / 2 * N_CORNER_ORI * N_UD);
	
	free(perfect_h_table);
}



