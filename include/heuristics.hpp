#ifndef heur_H
#define heur_H

#include "CoordCube.hpp"
#include "define.hpp"

int					phase_1_heuristic(CoordCube *coord_cube);
int					phase_1_perfect_heuristic(CoordCube& coord_cube);
// unsigned char*		phase_1_perfect_heuristic_table(void);

int	g_zero(int g);
int	g_plusone(int g);


#endif