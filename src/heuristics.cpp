#include "heuristics.hpp"
#include "utils.hpp"


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
		std::ifstream two(EDGE_ORI_HEURISTIC_NAME, std::ios_base::binary);
		std::ifstream thre(UD_SLICE1_HEURISTIC_NAME, std::ios_base::binary);

		if (in.good() == false || two.good() == false || thre.good() == false)
		{
			std::cout << "ERROR while reading heuristics tables pahse1, please check the existence of the following files:\n" << CORNER_ORI_HEURISTIC_NAME << "\n" << EDGE_ORI_HEURISTIC_NAME << "\n" << UD_SLICE1_HEURISTIC_NAME << std::endl;
			return (-1); // TODO: check ce retour
		}
		in.read((char*)h_table_c_ori, N_CORNER_ORI * sizeof(int));
		two.read((char*)h_table_e_ori, N_EDGE_ORI * sizeof(int));
		thre.read((char*)h_table_UD, N_UD * sizeof(int));

		// std::cout << "should only print once" << std::endl;
	}
	first = false;

	int out = 0;

	out = std::max(h_table_c_ori[coord_cube->corner_orientation_coord], h_table_UD[coord_cube->UD_slice_coord]);
	out = std::max(out, h_table_e_ori[coord_cube->edge_orientation_coord]);
	
	return (out);
}

int	phase_2_heuristic(CoordCube *coord_cube)
{
	static int h_table_c_perm[N_CORNER_PERMUTATION];
	static int h_table_e_perm[N_EDGE_PERMUTATION_2];
	static int h_table_UD2[N_UD_2];
	static bool first = true;

	if (first)
	{
				std::ifstream in(CORNER_PERM_HEURISTIC_NAME, std::ios_base::binary);
		std::ifstream two(EDGE_PERM_HEURISTIC_NAME, std::ios_base::binary);
		std::ifstream thre(UD_SLICE2_HEURISTIC_NAME, std::ios_base::binary);

		if (in.good() == false || two.good() == false || thre.good() == false)
		{
			std::cout << "ERROR while reading heuristics tables pahse2, please check the existence of the following files:\n" << CORNER_ORI_HEURISTIC_NAME << "\n" << EDGE_ORI_HEURISTIC_NAME << "\n" << UD_SLICE1_HEURISTIC_NAME << std::endl;
			return (-1); // TODO: check ce retour
		}
		in.read((char*)h_table_c_perm, N_CORNER_PERMUTATION * sizeof(int));
		two.read((char*)h_table_e_perm, N_EDGE_PERMUTATION_2 * sizeof(int));
		thre.read((char*)h_table_UD2, N_UD_2 * sizeof(int));

		// std::cout << "should only print once" << std::endl;
	}
	first = false;

	int out = 0;

	out = std::max(h_table_c_perm[coord_cube->corner_permutation_coord], h_table_UD2[coord_cube->UD_slice2_coord]);
	out = std::max(out, h_table_e_perm[coord_cube->edge_permutation_coord]);
	
	return (out);
}

void read_split_tables_file(char* table1, char* table2)
{
	std::ifstream out11(SPLIT_ONE_NAME, std::ios_base::binary);
	out11.read(table1, sizeof(char) * HSIZEONE / 2);
	std::ifstream out21(SPLIT_TWO_NAME, std::ios_base::binary);
	out21.read(table2, sizeof(char) * ((HSIZEONE / 2) + 1));
}


int		phase_1_perfect_heuristic(CoordCube& coord_cube)
{
	static char* table_1 = (char*)malloc(sizeof(char) * (HSIZEONE / 2));
	static char* table_2 = (char*)malloc(sizeof(char) * ((HSIZEONE / 2) + 1));
	static bool first = true;

	if (first)
	{
		read_split_tables_file(table_1, table_2);
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

