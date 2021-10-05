#ifndef MOVE_TABLES_H
#define MOVE_TABLES_H

#include "CoordCube.hpp"
#include "define.hpp"

int	phase_1_heuristic(CoordCube& coord_cube)
{
	static int h_table_c_ori[N_CORNER_ORI];
	static int h_table_UD[N_UD];
	static int h_table_e_ori[N_EDGE_ORI];

	int out(0);
	out = std::max(h_table_c_ori[coord_cube.corner_orientation_coord], h_table_UD[coord_cube.UD_slice_coord]);
	out = std::max(out, h_table_e_ori[coord_cube.edge_orientation_coord]);
	
	return (out);
}

#endif