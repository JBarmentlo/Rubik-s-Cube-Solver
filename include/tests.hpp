#ifndef TEST_HPP
#define TEST_HPP


#include "cubiecube_utils.hpp"
#include "CubieCube.hpp"

#include "utils.hpp"
typedef int (*get_coord_function)(cubiecube_t*);
typedef void (*set_coord_function)(int, cubiecube_t*);

void check_identity()
{
	cubiecube_t* moves = get_moves();
	cubiecube_t one;
	cubiecube_t two;
	cubiecube_t three;

	for (int i = 0; i < 6; i++)
	{
		one = moves[i];
		two = moves[i + 6];
		three = moves[i + 12];

		apply_move(&one, &three);
		print_corners(&one);
		print_edges(&one);
		one = moves[i];
		std::cout << std::endl;


		apply_move(&three, &one);
		print_corners(&three);
		print_edges(&three);
		three = moves[i + 12];
		std::cout << std::endl;


		apply_move(&two, &two);
		print_corners(&two);
		print_edges(&two);
		two = moves[i + 6];
		std::cout << std::endl;
		std::cout << std::endl;
	}
}


void check_identity_class()
{
	cubiecube_t* moves = get_moves();
	cubiecube_t one;
	cubiecube_t two;
	cubiecube_t three;

	CubieCube	cubo;
	cubo.set_solved();

	cubo.print_corners();
	cubo.print_edges();
	std::cout << std::endl;
	std::cout << std::endl;

	for (int i = 0; i < 6; i++)
	{
		std::cout << i << std::endl;

		one = moves[i];
		two = moves[i + 6];
		three = moves[i + 12];
		std::cout << std::endl;


		cubo.set_solved();
		cubo.multiply(&one);
		cubo.multiply(&three);
		cubo.print_corners();
		std::cout << std::endl;
		cubo.print_edges();
		std::cout << std::endl;

		cubo.set_solved();
		cubo.multiply(&two);
		two = moves[i + 6];
		cubo.multiply(&two);
		cubo.print_corners();
		std::cout << std::endl;
		cubo.print_edges();
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;

	}
}

void check_identity_class_corners()
{
	cubiecube_t* moves = get_moves();
	cubiecube_t one;
	cubiecube_t two;
	cubiecube_t three;

	CubieCube	cubo;
	cubo.set_solved();

	cubo.print_corners();
	cubo.print_edges();
	std::cout << std::endl;
	std::cout << std::endl;

	for (int i = 0; i < 6; i++)
	{
		std::cout << i << std::endl;

		one = moves[i];
		two = moves[i + 6];
		three = moves[i + 12];
		std::cout << std::endl;


		cubo.set_solved();
		cubo.multiply_corners(&one);
		cubo.multiply_corners(&three);
		cubo.print_corners();
		std::cout << std::endl;
		cubo.print_edges();
		std::cout << std::endl;

		cubo.set_solved();
		cubo.multiply_corners(&two);
		two = moves[i + 6];
		cubo.multiply_corners(&two);
		cubo.print_corners();
		std::cout << std::endl;
		cubo.print_edges();
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;

	}
}

void check_identity_class_edges()
{
	cubiecube_t* moves = get_moves();
	cubiecube_t one;
	cubiecube_t two;
	cubiecube_t three;

	CubieCube	cubo;
	cubo.set_solved();

	cubo.print_corners();
	cubo.print_edges();
	std::cout << std::endl;
	std::cout << std::endl;

	for (int i = 0; i < 6; i++)
	{
		std::cout << i << std::endl;

		one = moves[i];
		two = moves[i + 6];
		three = moves[i + 12];
		std::cout << std::endl;


		cubo.set_solved();
		cubo.multiply_edges(&one);
		cubo.multiply_edges(&three);
		cubo.print_corners();
		std::cout << std::endl;
		cubo.print_edges();
		std::cout << std::endl;

		cubo.set_solved();
		cubo.multiply_edges(&two);
		two = moves[i + 6];
		cubo.multiply_edges(&two);
		cubo.print_corners();
		std::cout << std::endl;
		cubo.print_edges();
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;

	}
}

void check_set_coords_1()
{
	CubieCube cubo;
	cubo.set_solved();

	for (int i = 0; i < 2187; i++)
	{
		cubo.set_corner_ori_coord(i);

		if (cubo.corner_ori_coord() != i)
		{
			std::cout << "C ori " << cubo.corner_ori_coord() << std::endl;
		}	
	}
	for (int i = 0; i < 2047; i++)
	{
		cubo.set_edge_ori_coord(i);
		if (cubo.edge_ori_coord() !=  i)
		{
			std::cout << "E ori " << cubo.edge_ori_coord() << std::endl;
		}
	}

	for (int i = 0; i < 495; i++)
	{
		cubo.set_UD_coord(i);
		// std::cout << "UD " << cubo.UD_coord() << std::endl;

		if (cubo.UD_coord() !=  i)
		{
			std::cout << "UD " << cubo.UD_coord() << std::endl;
		}
	}
}

void check_set_get_coord_equivalency(get_coord_function get_coord, set_coord_function set_coord, int range)
{
	CubieCube cube;
	cube.set_solved();

	for (int i = 0; i < range; i++)
	{
		set_coord(i, &cube.data);
		if (get_coord(&cube.data) != i)
		{
			std::cout << "COORD ERROR " << i << std::endl;
		}
	}
}

void check_all_coords(void)
{
	for (int i = 0; i < N_TABLES; i++)
	{
		std::cout << "Checking coord " << table_file_names[i] << std::endl;
		check_set_get_coord_equivalency(coord_getters[i], coord_setters[i], coord_range[i]);
	}
}
#endif
