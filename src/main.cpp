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
	for (int i; i <  N_MOVES; i++)
	{
		int move = rand() % 18;
		cub.apply_move(move);
		std::cout << i << ",  " << move;
		std::cout << " h: " << phase_1_perfect_heuristic(cub) << std::endl;
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
	// backwards_fill_h_table(9);

	CoordCube begin(0);
	for (int i = 0; i < 16; i++)
	{
		CoordCube begin(0);
		// begin.apply_move(i);
		begin = begin.create_baby_from_move_stack(i);
		std::cout << i << std::endl;
		for (int j = 0; j < 16; j++)
		{
			CoordCube bb = begin.create_baby_from_move_stack(j);
			std::cout << bb.flat_coord() << " : "<< phase_1_perfect_heuristic(bb) << std::endl;
		}
		std::cout << std::endl;
		std::cout << std::endl;
	}
	test_h();
	test_h();
	test_h();
	test_h();
	test_h();
	test_h();
	test_h();
	test_h();

	// phase_one_solver(begin);

	// }
	return true;
}
