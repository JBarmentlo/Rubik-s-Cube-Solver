#include "heuristics_tables.hpp"
#include "CoordCube.hpp"
#include "utils.hpp"

#include <thread>
#include <string>
#include <mutex>


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



static std::mutex mutexes[N_MUTEX] = {std::mutex(), std::mutex(), std::mutex(), std::mutex(), std::mutex(), std::mutex(), std::mutex(), std::mutex(), std::mutex(), std::mutex(), std::mutex(), std::mutex(), std::mutex(), std::mutex(), std::mutex(), std::mutex(), std::mutex(), std::mutex(), std::mutex(), std::mutex(), std::mutex(), std::mutex(), std::mutex(), std::mutex(), std::mutex(), std::mutex(), std::mutex(), std::mutex(), std::mutex(), std::mutex(), std::mutex(), std::mutex()};

char* h_table_1 = (char*)malloc(sizeof(char) * (HSIZEONE / 2));
char* h_table_2 = (char*)malloc(sizeof(char) * ((HSIZEONE / 2) + 1)); 
std::mutex print;



inline void write_split_table(int value, unsigned int index)
{
	mutexes[index % N_MUTEX].lock();
	if (index < HSIZEONE / 2)
	{
		h_table_1[index] = value;
	}
	if (index >= HSIZEONE / 2)
	{
		h_table_2[index - (HSIZEONE / 2)] = value;
	}
	mutexes[index % N_MUTEX].unlock();
}

inline void write_no_mutex_split_table(int value, unsigned int index)
{
	if (index < HSIZEONE / 2)
	{
		h_table_1[index] = value;
	}
	else
	{
		h_table_2[index - (HSIZEONE / 2)] = value;
	}
}

inline bool write_smaller_split_table(int value, unsigned int index)
{
	mutexes[index % N_MUTEX].lock();
	if (index < HSIZEONE / 2)
	{
		if (h_table_1[index] > value)
		{
			h_table_1[index] = value;
			mutexes[index % N_MUTEX].unlock();
			// print.lock();
			// std::cout << "Writing: \t" << value << " at: \t" << index << std::endl;
			// print.unlock();
			return true;
		}
	}
	else
	{
		if (h_table_2[index - (HSIZEONE / 2)] > value)
		{
			h_table_2[index - (HSIZEONE / 2)] = value;
			mutexes[index % N_MUTEX].unlock();
			return true;
		}
	}
	mutexes[index % N_MUTEX].unlock();
	return false;
}

inline int 	read_write_smaller_split_table(int value, unsigned int index)
{
	// Writes new value if smaller than current value and returns pre-write value at index;
	int tmp;
	mutexes[index % N_MUTEX].lock();
	if (index < HSIZEONE / 2)
	{
		tmp = h_table_1[index];
		if (tmp > value)
		{
			h_table_1[index] = value;
		}
	}
	else
	{
		tmp = h_table_2[index - (HSIZEONE / 2)];
		if (tmp > value)
		{
			h_table_2[index - (HSIZEONE / 2)] = value;
		}
	}
	mutexes[index % N_MUTEX].unlock();
	return tmp;
}

inline bool write_smaller_equal_split_table(int value, unsigned int index)
{
	mutexes[index % N_MUTEX].lock();
	if (index < HSIZEONE / 2)
	{
		if (h_table_1[index] >= value)
		{
			h_table_1[index] = value;
			mutexes[index % N_MUTEX].unlock();
			return true;
		}
	}
	else
	{
		if (h_table_2[index - (HSIZEONE / 2)] >= value)
		{
			h_table_2[index - (HSIZEONE / 2)] = value;
			mutexes[index % N_MUTEX].unlock();
			return true;
		}
	}
	mutexes[index % N_MUTEX].unlock();
	return false;
}

inline char read_split_table(unsigned int index)
{
	mutexes[index % N_MUTEX].lock();
	if (index < HSIZEONE / 2)
	{
		return h_table_1[index];
	}
	else
	{
		return h_table_2[index - HSIZEONE / 2];
	}
	mutexes[index % N_MUTEX].unlock();
}

inline char read_no_mutex_split_table(unsigned int index)
{
	if (index < HSIZEONE / 2)
	{
		return h_table_1[index];
	}
	else
	{
		return h_table_2[index - HSIZEONE / 2];
	}
}


void my_walk(CoordCube cube, const int steps, const int limit, const int daddy_move)
{
	if (steps > limit)
		return;
	
	if (not write_smaller_split_table(steps, cube.flat_coord()))
		return;
	
	for (int i = 0; i < N_MOVES; i++)
	{
		if (i % 6 != daddy_move % 6)
		{
			my_walk(cube.create_baby_from_move_stack(i), steps + 1, limit, daddy_move);
		}
	}
}


void start_one_thread(CoordCube cube, int first_move, int last_move, int limit)
{
	print.lock();
	std::cout << "starting thread for moves " << first_move << " - " << last_move << std::endl;
	print.unlock();
	for (int i = first_move; i <= last_move; i++)
	{
		my_walk(cube.create_baby_from_move_stack(i), 1, limit, i);
	}
}

void start_threads_my_walk(CoordCube start, int limit)
{
	std::thread thread_arr[N_THREADS];
	int			last_thread = 0;

	for (int i = 0; i < N_MOVES; i++)
	{
		if (i % (N_MOVES / N_THREADS) == 0)
		{

			thread_arr[last_thread] = std::thread(&start_one_thread, start, last_thread * (N_MOVES / N_THREADS), (last_thread + 1) * (N_MOVES / N_THREADS) - 1, limit);
			last_thread += 1;
		}
	}
	for (int i = 0; i < N_THREADS; i++)
	{
		thread_arr[i].join();
	}
}

int	my_back_walk(CoordCube cube, int steps, int limit, int daddy_move)
{
	int h_val;

	if (steps > limit)
	{
		std::cout << "should never print" << std::endl;
		return (UNFILLED);
	}

	h_val = read_split_table(cube.flat_coord());
	if (h_val != UNFILLED)
		return h_val + 1;

	for (int i = 0; i < N_MOVES; i++)
	{
		if ((steps == 0) or (daddy_move % 6 != i % 6))
			h_val = std::min(h_val, my_back_walk(cube.create_baby_from_move_stack(i), steps + 1, limit, i));
	}

	write_smaller_split_table(h_val, cube.flat_coord());
	return (h_val + 1);

}

void start_one_thread_backwards(CoordCube cube, int first_move, int last_move, int limit)
{
	for (int i = first_move; i <= last_move; i++)
	{
		my_walk(cube.create_baby_from_move_stack(i), 0, limit, i);
	}
}

void start_threads_my_backwards_walk(CoordCube start, int limit)
{
	std::thread thread_arr[N_THREADS];
	int			last_thread = 0;

	for (int i = 0; i < N_MOVES; i++)
	{
		if (i % (N_MOVES / N_THREADS) == 0)
		{

			thread_arr[last_thread] = std::thread(&start_one_thread_backwards, start, last_thread * (N_MOVES / N_THREADS), (last_thread + 1) * (N_MOVES / N_THREADS) - 1, limit);
			last_thread += 1;
		}
	}
	for (int i = 0; i < N_THREADS; i++)
	{
		thread_arr[i].join();
	}
}


void backwards_fill_h_table(int limit)
{
	for (unsigned int i = 0; i < HSIZEONE; i++)
	{
		write_no_mutex_split_table(UNFILLED, i);
		if (read_no_mutex_split_table(i) != UNFILLED)
			std::cout << "/* message */" << std::endl;
	}
	write_no_mutex_split_table(0,0);
	start_threads_my_walk(CoordCube(0), limit);

	std::cout << "Done forward" << std::endl;
	std::ofstream out11("tables/onehalf", std::ios_base::binary);
	out11.write(h_table_1, sizeof(char) * HSIZEONE / 2);
	out11.close();
	std::ofstream out21("tables/twohalf", std::ios_base::binary);
	out21.write(h_table_2, sizeof(char) * ((HSIZEONE / 2) + 1));
	std::cout << "Done writing INTERMEDIATE STAGE" << std::endl;
	out21.close();
	// std::ifstream in("tables/onehalf", std::ios_base::binary);
	// in.read(h_table_1, sizeof(char) * HSIZEONE / 2);
	// std::ifstream in2("tables/twohalf", std::ios_base::binary);
	// in2.read((char*)h_table_2, sizeof(char) * ((HSIZEONE / 2) + 1));

	for (unsigned int i = 0; i < HSIZEONE; i++)
	{
		if (i % (N_EDGE_ORI / 512 * N_CORNER_ORI * N_UD) == 0)
		{
			std::cout << "back: " <<  i / (N_EDGE_ORI / 512 * N_CORNER_ORI * N_UD) << " / 512" << std::endl;
		}
		if (read_no_mutex_split_table(i) == UNFILLED)
			my_back_walk(CoordCube(i), 0, 3, 0);
	}
	std::cout << "done back walk" << std::endl;

	std::ofstream out("../tables/onehalf", std::ios_base::binary);
	out.write(h_table_1, sizeof(char) * HSIZEONE / 2);
	std::ofstream out2("../tables/twohalf", std::ios_base::binary);
	out2.write(h_table_2, sizeof(char) * ((HSIZEONE / 2) + 1));
	std::cout << "done writing" << std::endl;
	
	free(h_table_1);
	free(h_table_2);
}

// void make_perfect_move_table()
// {
// 	std::ifstream in("tables/onehalf", std::ios_base::binary);
// 	in.read(h_table_1, sizeof(char) * HSIZEONE / 2);
// 	std::ofstream in2("tables/twohalf", std::ios_base::binary);
// 	in2.read((char*)h_table_2, sizeof(char) * ((HSIZEONE / 2) + 1));
	
// 	int min = 123456;
// 	int min_move = 123456;
// 	unsigned char* perfect_move_table = (unsigned char*)malloc(sizeof(char) * N_EDGE_ORI / 2 * N_CORNER_ORI * N_UD + 1);

// 	for (unsigned int i = 0; i < HSIZEONE; i++)
// 	{
// 		min = 123456;
// 		for (int j = 0; j < N_MOVES; j++)
// 		{
// 			CoordCube cube(i);
// 			cube.apply_move(j);
// 			if (cube.flat_coord() < min)
// 			{
// 				min = cube.flat_coord();
// 				min_move = j;
// 			}
// 		}
// 		write_half_char_table(perfect_move_table, min_move)
// 	}
// }
