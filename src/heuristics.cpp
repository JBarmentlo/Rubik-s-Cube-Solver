#include "heuristics.hpp"
#include "utils.hpp"


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


int		phase_1_perfect_heuristic(CoordCube& coord_cube)
{
	static char* table_1 = (char*)malloc(sizeof(char) * (HSIZEONE / 2));
	static char* table_2 = (char*)malloc(sizeof(char) * ((HSIZEONE / 2) + 1));
	static bool first = true;

	if (first)
	{
		std::ifstream in("../tables/onehalf", std::ios_base::binary);
		in.read(table_1, sizeof(char) * HSIZEONE / 2);
		std::ifstream in2("../tables/twohalf", std::ios_base::binary);
		in2.read((char*)table_2, sizeof(char) * ((HSIZEONE / 2) + 1));
	}
	first = false;

	int index = coord_cube.flat_coord();
	if (index < HSIZEONE / 2)
	{
		return table_1[index];
	}
	else
	{
		return table_2[index - HSIZEONE / 2];
	}
}

// unsigned char*		phase_1_perfect_heuristic_table(void)
// {
// 	static unsigned char h_tableo[N_EDGE_ORI / 2 * N_UD * N_CORNER_ORI];
// 	static bool first = true;

// 	if (first)
// 	{
// 		std::ifstream in(PHASE_ONE_HEURISTIC_NAME, std::ios_base::binary);
// 		in.read((char*)h_tableo, sizeof(char) * (N_EDGE_ORI / 2 * N_UD * N_CORNER_ORI));
// 		std::cout << "should print once" << std::endl;
// 	}
// 	first = false;
// 	return h_tableo;
// }

