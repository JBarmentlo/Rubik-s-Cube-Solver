#include "Node.hpp"
#include "ida.hpp"
#include "CoordCube.hpp"
#include "ida_utils.hpp"
#include "heuristics.hpp"
#include "heuristics_tables.hpp"
#include "utils.hpp"


#include "cubiecube_utils.hpp"
#include "CubieCube.hpp"
// #include "tests.hpp"
// #include "move_tables.hpp"

void 	print_table_depth(int d, int depth, CoordCube cub)
{
	if (d == 0)
	{
		if (phase_1_perfect_heuristic(cub) > depth)
		{
			std::cout << cub.flat_coord() << ": " << phase_1_perfect_heuristic(cub) << " " ;
		}
		return;
	}
	for (int i = 0; i < N_MOVES; i++)
	{
		CoordCube bb1 = cub.create_baby_from_move_stack(i);
		print_table_depth(d - 1, depth + 1,  bb1);
		// std::cout << "move: " << i << std::endl;
	}
}

void test_h(void)
{
	CoordCube cub(0, 0, 0);
	std::cout << "Testing ";
	std::cout << "h " << phase_1_perfect_heuristic(cub) << std::endl;
	for (int i; i <  5; i++)
	{
		int move = rand() % 18;
		cub.apply_move(move);
		std::cout << i << " " << move << std::endl;
		std::cout << phase_1_perfect_heuristic(cub) << std::endl;
		std::cout << std::endl;
	}
	
}


inline void print_bits(unsigned char c)
{
	for (int i = 0; i < 8; i++)
	{
		if (c >> 7 != 0)
		{
			std::cout << 1;
		}
		else
		{
			std::cout << 0;
		}
		c = c << 1;
	}
	std::cout << std::endl;
}

float			get_h_filling()
{
	unsigned int size =  N_EDGE_ORI * N_CORNER_ORI * N_UD;
	unsigned int full = 0;

	for (unsigned int i; i < size; i++)
	{
		CoordCube c = CoordCube(i);
		if (phase_1_perfect_heuristic(c) != 15)
		{
			full = full + 1;
		}
	}
	return (float(full) / float(size));
}

int		main(void)
{



	// for (int i = 1; i < 100; i++)
	// {
	// 	CoordCube begin = CoordCube(0, 0, 0);
	// 	CubieCube test = CubieCube();
	// 	test.set_solved();

	// 	test.multiply(&get_moves()[i % 18]);
	// 	begin.apply_move(i% 18);
	// 	// begin.apply_move(15);
	// 	std::cout << begin.flat_coord() << std::endl;
	// 	std::cout << begin.flat_coord() << std::endl;
	// 	std::cout << std::endl;
	// }

	
	// for (unsigned int i = limit;  i > 0; i--)
	// {
	// 	// std::cout << "i " << i << std::endl;
	// 	if (phase_1_perfect_heuristic(CoordCube(i)) == (unsigned char)15)
	// 	{
	// 		std::cout << phase_1_perfect_heuristic(CoordCube(i)) << std::endl;
	// 	}
	// }
	// make_all_move_tables();
	// int limit = 12;
	// make_perfect_heuristics_table();
	make_perfect_heuristics_table_iterative(13);
	// test_h();
	std::cout << "FIlling %: " << get_h_filling() << std::endl;
	for (int i = 1; i <= 7; i++)
	{
		std::cout << "table depth " << i << std::endl;
		print_table_depth(i, 0, CoordCube(0,0,0));
		std::cout << std::endl;
		std::cout << std::endl;

	}
	return true;
}
