#include "heuristics_tables.hpp"
#include "CoordCube.hpp"
#include "utils.hpp"

#include <thread>
#include <string>
#include <mutex>
#include <shared_mutex>
#include <queue>

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

int*	create_heuristics_table(int size, reading_table_function read)
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
		std::cout << "heuristic table created in: " << EDGE_ORI_HEURISTIC_NAME << " of size : " << N_EDGE_ORI_1<< std::endl;
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
		std::cout << "heuristic table created in: " << UD_SLICE1_HEURISTIC_NAME << " of size : " << N_UD_1<< std::endl;
	}
	else
		std::cout << "PATH ERROR: can't create the following file" << UD_SLICE1_HEURISTIC_NAME << std::endl;
		
	free(UD_slice_h_table);
}

static std::shared_mutex mutexes[N_MUTEX] = {std::shared_mutex(), std::shared_mutex(), std::shared_mutex(), std::shared_mutex(), std::shared_mutex(), std::shared_mutex(), std::shared_mutex(), std::shared_mutex(), std::shared_mutex(), std::shared_mutex(), std::shared_mutex(), std::shared_mutex(), std::shared_mutex(), std::shared_mutex(), std::shared_mutex(), std::shared_mutex(), std::shared_mutex(), std::shared_mutex(), std::shared_mutex(), std::shared_mutex(), std::shared_mutex(), std::shared_mutex(), std::shared_mutex(), std::shared_mutex(), std::shared_mutex(), std::shared_mutex(), std::shared_mutex(), std::shared_mutex(), std::shared_mutex(), std::shared_mutex(), std::shared_mutex(), std::shared_mutex()};

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
	mutexes[index % N_MUTEX].lock_shared();
	if (index < HSIZEONE / 2)
	{
		mutexes[index % N_MUTEX].unlock_shared();
		return h_table_1[index];
	}
	else
	{
		mutexes[index % N_MUTEX].unlock_shared();
		return h_table_2[index - HSIZEONE / 2];
	}
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


void thread_print(std::string str)
{
	print.lock();
	std::cout << str << std::endl;

	print.unlock();
}

void my_walk(CoordCube cube, const int steps, const int limit, const int daddy_move)
{
	if (steps > limit)
		return;

	if (not write_smaller_split_table(steps, cube.flat_coord()))
		return;
	
	for (int i = 0; i < N_MOVES; i++)
	{
		my_walk(cube.create_baby_from_move_stack(i), steps + 1, limit, daddy_move);
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

int	 my_back_walk(CoordCube cube, int steps, int limit, int daddy_move)
{
	int h_val;

	if (steps > limit)
	{
		return (UNFILLED);
	}

	h_val = read_split_table(cube.flat_coord());
	if (h_val != UNFILLED)
		return h_val + 1;

	for (int i = 0; i < N_MOVES; i++)
	{
		if (steps == 0 or (daddy_move % 6 != i % 6))
			h_val = std::min(h_val, my_back_walk(cube.create_baby_from_move_stack(i), steps + 1, limit, i));
	}
	// std::cout << "write" << std::endl;
	write_smaller_split_table(h_val, cube.flat_coord());
	// std::cout << "out write" << std::endl;
	return (h_val + 1);

}

std::mutex	min_ret_mutex;
void start_one_thread_backwards(CoordCube cube, int first_move, int last_move, int limit, int& ret)
{
	int	min_val = UNFILLED;

	for (int i = first_move; i <= last_move; i++)
	{
		min_val = std::min(my_back_walk(cube.create_baby_from_move_stack(i), 1, limit, i), min_val);
	}
	min_ret_mutex.lock();
	if (ret > min_val)
		ret = min_val;
	min_ret_mutex.unlock();
}

void start_threads_my_backwards_walk(CoordCube start, int limit)
{
	std::thread thread_arr[N_THREADS];
	int			last_thread = 0;
	int			min_return = UNFILLED;

	for (int i = 0; i < N_MOVES; i++)
	{
		if (i % (N_MOVES / N_THREADS) == 0)
		{

			thread_arr[last_thread] = std::thread(&start_one_thread_backwards, start, last_thread * (N_MOVES / N_THREADS), (last_thread + 1) * (N_MOVES / N_THREADS) - 1, limit, std::ref(min_return));
			last_thread += 1;
		}
	}
	for (int i = 0; i < N_THREADS; i++)
	{
		thread_arr[i].join();
	}
	write_smaller_split_table(min_return, start.flat_coord());
}

void write_split_tables_file()
{
	std::cout << "Writing split table to file" << std::endl;
	std::ofstream out11(SPLIT_ONE_NAME, std::ios_base::binary);
	out11.write(h_table_1, sizeof(char) * HSIZEONE / 2);
	std::ofstream out21(SPLIT_TWO_NAME, std::ios_base::binary);
	out21.write(h_table_2, sizeof(char) * ((HSIZEONE / 2) + 1));
	std::cout << "Done writing " << std::endl;
}

void read_split_tables_file()
{
	std::cout << "reading split table to file" << std::endl;
	std::ifstream out11(SPLIT_ONE_NAME, std::ios_base::binary);
	out11.read(h_table_1, sizeof(char) * HSIZEONE / 2);
	std::ifstream out21(SPLIT_TWO_NAME, std::ios_base::binary);
	out21.read(h_table_2, sizeof(char) * ((HSIZEONE / 2) + 1));
	std::cout << "Done reading " << std::endl;
}

void backwards_fill_h_table(int limit)
{
	for (unsigned int i = 0; i < HSIZEONE; i++)
	{
		write_no_mutex_split_table(UNFILLED, i);
	}
	// read_split_tables_file();

	write_no_mutex_split_table(0,0);
	start_threads_my_walk(CoordCube(0), limit);

	std::cout << "Done forward" << std::endl;
	write_split_tables_file();
	std::thread thread_array[N_THREADS];
	std::queue<std::thread>  thread_q;
	int			back_walk_counter = 0;

	for (unsigned int i = 0; i < HSIZEONE; i++)
	{
		// std::cout << i << std::endl;
		if (i % (N_EDGE_ORI_1/ 1024 * N_CORNER_ORI * N_UD) == 0)
		{
			std::cout << "back: " <<  i / (N_EDGE_ORI_1/ 1024 * N_CORNER_ORI * N_UD) << " / 1024" << std::endl;
		}
		if (read_no_mutex_split_table(i) == UNFILLED)
		{
			// start_threads_my_backwards_walk(CoordCube(i), 12 - limit);
			if (thread_q.size() < N_THREADS)
			{
				thread_q.push(std::thread(my_back_walk, CoordCube(i), 0, 12 - limit, 0));
			}
			else
			{
				thread_q.front().join();
				thread_q.pop();
				thread_q.push(std::thread(my_back_walk, CoordCube(i), 0, 12 - limit, 0));
			}
		}
	}
	while (not thread_q.empty())
	{
		thread_q.front().join();
		thread_q.pop();
	}
	std::cout << "done back walk" << std::endl;

	write_split_tables_file();
	
	free(h_table_1);
	free(h_table_2);
}

// void make_perfect_move_table()
// {
// 	std::ifstream in(SPLIT_ONE_NAME, std::ios_base::binary);
// 	in.read(h_table_1, sizeof(char) * HSIZEONE / 2);
// 	std::ofstream in2(SPLIT_TWO_NAME, std::ios_base::binary);
// 	in2.read((char*)h_table_2, sizeof(char) * ((HSIZEONE / 2) + 1));
	
// 	int min = 123456;
// 	int min_move = 123456;
// 	unsigned char* perfect_move_table = (unsigned char*)malloc(sizeof(char) * N_EDGE_ORI_1/ 2 * N_CORNER_ORI * N_UD_1+ 1);

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

