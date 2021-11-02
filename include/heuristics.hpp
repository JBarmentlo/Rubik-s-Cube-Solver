#ifndef HEURISTIC_HPP
#define HEURISTIC_HPP

#include "CoordCube.hpp"
// #include "define.hpp"

typedef int (*heuristic_function)(CoordCube);
typedef int (*g_function)(int g);

// int					phase_1_heuristic(CoordCube *coord_cube);
// int					phase_1_perfect_heuristic(CoordCube& coord_cube);
// unsigned char*		phase_1_perfect_heuristic_table(void);

int	g_zero(int g);
int	g_plusone(int g);

// int		phase_1_heuristic(CoordCube *coord_cube);
// int     	phase_2_heuristic(CoordCube *coord_cube);
// void 	write_table_to_cpp(void);
// void 	make_move_table(void);
// int 		get_perfect_move_phase_1(CoordCube cube);
int 	get_move_for_cube(CoordCube cube);
int     phase_1_perfect_heuristic_seek(CoordCube& coord_cube);
int     phase_2_heuristic(CoordCube coord_cube);




#endif