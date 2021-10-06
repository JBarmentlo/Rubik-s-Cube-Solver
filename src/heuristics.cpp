#include "heuristics.hpp"

int	g_zero(int g)
{
	return(0);
}

int	g_plusone(int g)
{
	return(g + 1);
}

int	phase_1_heuristic(CoordCube *coord_cube)
{
	static int h_table_c_ori[N_CORNER_ORI];
	static int h_table_e_ori[N_EDGE_ORI];
	static int h_table_UD[N_UD];
	static bool first = true;

	if (first)
	{
		std::ifstream in(CORNER_ORI_HEURISTIC_NAME, std::ios_base::binary);
		in.read((char*)h_table_c_ori, N_CORNER_ORI * sizeof(int));

		std::ifstream two(EDGE_ORI_HEURISTIC_NAME, std::ios_base::binary);
		two.read((char*)h_table_e_ori, N_EDGE_ORI * sizeof(int));

		std::ifstream thre(UD_SLICE_HEURISTIC_NAME, std::ios_base::binary);
		thre.read((char*)h_table_UD, N_UD * sizeof(int));
		std::cout << "should print once" << std::endl;
	}
	first = false;

	int out = 0;

	out = std::max(h_table_c_ori[coord_cube->corner_orientation_coord], h_table_UD[coord_cube->UD_slice_coord]);
	out = std::max(out, h_table_e_ori[coord_cube->edge_orientation_coord]);
	
	return (out);
}
