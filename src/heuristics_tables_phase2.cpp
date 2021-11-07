#include "heuristics_tables.hpp"

#include <thread>
#include <string>
#include <mutex>
#include <shared_mutex>
#include <queue>


static std::shared_mutex mutexes2[N_MUTEX] = {std::shared_mutex(), std::shared_mutex(), std::shared_mutex(), std::shared_mutex(), std::shared_mutex(), std::shared_mutex(), std::shared_mutex(), std::shared_mutex(), std::shared_mutex(), std::shared_mutex(), std::shared_mutex(), std::shared_mutex(), std::shared_mutex(), std::shared_mutex(), std::shared_mutex(), std::shared_mutex(), std::shared_mutex(), std::shared_mutex(), std::shared_mutex(), std::shared_mutex(), std::shared_mutex(), std::shared_mutex(), std::shared_mutex(), std::shared_mutex(), std::shared_mutex(), std::shared_mutex(), std::shared_mutex(), std::shared_mutex(), std::shared_mutex(), std::shared_mutex(), std::shared_mutex(), std::shared_mutex()};

char* table_1 = (char*)malloc(sizeof(char) * (HSIZETWO_1));
// char* h_table_2 = (char*)malloc(sizeof(char) * ((HSIZEONE / 2) + 1)); 
std::mutex print2;
int moves_phase_2[10] = {0, 3, 6, 7, 8, 9, 10, 11, 12, 15};

inline void write_table_1(int value, unsigned int index)
{
	mutexes2[index % N_MUTEX].lock();
	table_1[index] = value;
	mutexes2[index % N_MUTEX].unlock();
}

inline bool write_smaller_table_1(int value, unsigned int index)
{
	mutexes2[index % N_MUTEX].lock();
	if (table_1[index] < value)
	{
		table_1[index] = value;
		mutexes2[index % N_MUTEX].unlock();
		return(true);
	}
	mutexes2[index % N_MUTEX].unlock();
	return(false);
}

void walk_1(CoordCube cube, const int steps, const int limit, const int daddy_move)
{
	if (steps > limit)
		return;

	if (not write_smaller_table_1(steps, cube.flat_coord_2_1()))
		return;

	for (int i = 0; i < N_MOVES_PHASE_2; i++)
	{
		walk_1(cube.create_baby_from_move_phase2(i), steps + 1, limit, daddy_move);
	}
}

void start_one_thread_1(CoordCube cube, int first_move_index, int last_move_index, int limit)
{
	print2.lock();
	std::cout << "starting thread for moves (indexes) " << first_move_index << " - " << last_move_index << std::endl;
	print2.unlock();
	for (int i = first_move_index; i < last_move_index; i++)
	{
		if (i < N_MOVES_PHASE_2)
			walk_1(cube.create_baby_from_move_phase2(moves_phase_2[i]), 1, limit, i);
	}
}

void start_threads_1(CoordCube start, int limit)
{
	std::thread thread_arr[N_THREADS];
	int			last_thread = 0;

	for (int i = 0; i < N_THREADS; i++)
	{
		thread_arr[last_thread] = std::thread(&start_one_thread_1, start, i * N_MOVES_PHASE_2 / N_THREADS, (i + 1) * N_MOVES_PHASE_2 / N_THREADS, limit);
		last_thread += 1;
	}
	for (int i = 0; i < N_THREADS; i++)
	{
		thread_arr[i].join();
	}
}

void testo(void)
{
	CoordCube cube = CoordCube();
	start_threads_1(cube, 18);
}