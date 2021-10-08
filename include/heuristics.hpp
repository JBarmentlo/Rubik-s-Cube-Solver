#ifndef heur_H
#define heur_H

#include "CoordCube.hpp"
#include "define.hpp"

int	g_zero(int g);
int	g_plusone(int g);

int		phase_1_heuristic(CoordCube *coord_cube);
int     phase_2_heuristic(CoordCube *coord_cube);


#endif