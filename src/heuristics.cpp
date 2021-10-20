#include "heuristics.hpp"
// #include "utils.hpp"

// #include <stdio.h>
// #include <string>

int	g_zero(int g)
{
	return(0);
}

int	g_plusone(int g)
{
	return(g + 1);
}

// int	phase_1_heuristic(CoordCube *coord_cube)
// {
// 	static int h_table_c_ori[N_CORNER_ORI_1];
// 	static int h_table_e_ori[N_EDGE_ORI_1];
// 	static int h_table_UD[N_UD_1];
// 	static bool first = true;

// 	if (first)
// 	{
// 		std::ifstream in(CORNER_ORI_HEURISTIC_NAME, std::ios_base::binary);
// 		std::ifstream two(EDGE_ORI_HEURISTIC_NAME, std::ios_base::binary);
// 		std::ifstream thre(UD_SLICE1_HEURISTIC_NAME, std::ios_base::binary);

// 		if (in.good() == false || two.good() == false || thre.good() == false)
// 		{
// 			std::cout << "ERROR while reading heuristics tables pahse1, please check the existence of the following files:\n" << CORNER_ORI_HEURISTIC_NAME << "\n" << EDGE_ORI_HEURISTIC_NAME << "\n" << UD_SLICE1_HEURISTIC_NAME << std::endl;
// 			return (-1); // TODO: check ce retour
// 		}
// 		in.read((char*)h_table_c_ori, N_CORNER_ORI_1 * sizeof(int));
// 		two.read((char*)h_table_e_ori, N_EDGE_ORI_1* sizeof(int));
// 		thre.read((char*)h_table_UD, N_UD_1* sizeof(int));

// 		// std::cout << "should only print once" << std::endl;
// 	}
// 	first = false;

// 	int out = 0;

// 	out = std::max(h_table_c_ori[coord_cube->corner_orientation_coord], h_table_UD[coord_cube->UD_slice_coord]);
// 	out = std::max(out, h_table_e_ori[coord_cube->edge_orientation_coord]);
	
// 	return (out);
// }


int	phase_2_heuristic(CoordCube coord_cube)
{
	static int h_table_c_perm[N_CORNER_PERMUTATION_2];
	static int h_table_e_perm[N_EDGE_PERMUTATION_2];
	static int h_table_UD2[N_UD_2];
	static bool first = true;

	if (first)
	{
		std::ifstream in(CORNER_PERM_2_HEURISTIC_NAME, std::ios_base::binary);
		std::ifstream two(EDGE_PERM_2_HEURISTIC_NAME, std::ios_base::binary);
		std::ifstream thre(UD_SLICE_2_HEURISTIC_NAME, std::ios_base::binary);

		if (in.good() == false || two.good() == false || thre.good() == false)
		{
			std::cout << "ERROR while reading heuristics tables pahse2, please check the existence of the following files:\n" << CORNER_ORI_HEURISTIC_NAME << "\n" << EDGE_ORI_HEURISTIC_NAME << "\n" << UD_SLICE1_HEURISTIC_NAME << std::endl;
			return (-1); // TODO: check ce retour
		}
		in.read((char*)h_table_c_perm, N_CORNER_PERMUTATION_2 * sizeof(int));
		two.read((char*)h_table_e_perm, N_EDGE_PERMUTATION_2 * sizeof(int));
		thre.read((char*)h_table_UD2, N_UD_2 * sizeof(int));

		// std::cout << "should only print once" << std::endl;
	}
	first = false;

	int out = 0;

	out = std::max(h_table_c_perm[coord_cube.corner_permutation_coord_2], h_table_UD2[coord_cube.UD_slice_coord_2]);
	out = std::max(out, h_table_e_perm[coord_cube.edge_permutation_coord_2]);
	
	return (out);
}


// void read_tables_file(char* table1, char* table2)
// {
// 	std::ifstream out11(SPLIT_ONE_NAME, std::ios_base::binary);
// 	out11.read(table1, sizeof(char) * (HSIZEONE / 2));
// 	std::ifstream out12(SPLIT_TWO_NAME, std::ios_base::binary);
// 	out12.read(table2, sizeof(char) * ((HSIZEONE / 2) + 1));
// }


int	phase_1_perfect_heuristic_seek(CoordCube& coord_cube)
{
	// static char* table_1 = (char*)malloc(sizeof(char) * (HSIZEONE));
	std::ifstream t1(SPLIT_ONE_NAME, std::ios_base::binary);
	std::ifstream t2(SPLIT_TWO_NAME, std::ios_base::binary);

	char out[2];
	long long index = coord_cube.flat_coord();
	// fseeko64(f, cube.flat_coord(), SEEK_SET);
	// char t[5] = fgets(out, 1, f);
	// std::cout << "t " << t << std::endl;

	if (index < (HSIZEONE / 2))
	{
		t1.seekg(index, std::ios::beg);
		t1.read(out, 1);
	}
	else
	{
		t2.seekg(index - (HSIZEONE / 2), std::ios::beg);
		t2.read(out, 1);
	}
	return out[0];
}

// int	phase_1_perfect_heuristic(CoordCube& coord_cube)
// {
// 	// static char* table_1 = (char*)malloc(sizeof(char) * (HSIZEONE));
// 	static char* table1 = (char*)malloc(sizeof(char) * (HSIZEONE / 2));
// 	static char* table2 = (char*)malloc(sizeof(char) * ((HSIZEONE / 2) + 1));
// 	static bool first = true;

// 	if (first)
// 	{
// 		read_tables_file(table1, table2);
// 	}
// 	first = false;

// 	unsigned int index = coord_cube.flat_coord();
// 	if (index < (HSIZEONE / 2))
// 	{
// 		return table1[index];
// 	}
// 	else
// 	{
// 		return table2[index - (HSIZEONE / 2)];
// 	}
// }

int get_move_for_cube(CoordCube cube)
{
	int min = MAX_INT;
	int min_move;
	int h;
	for (int i = 0; i < N_MOVES; i++)
	{
		CoordCube bb = cube.create_baby_from_move_phase1(i); // TODO CHECK IF OK phase2??
		h = phase_1_perfect_heuristic_seek(bb);
		if (h < min)
		{
			min = h;
			min_move = i;
		}
	}
	return (min_move);
}

// int get_perfect_move_phase_1(CoordCube cube)
// {
// 	// static FILE* f = fopen(PHASE_ONE_HEURISTIC_NAME, "rb");
// 	static std::ifstream in(PHASE_ONE_HEURISTIC_NAME, std::ios_base::binary);
// 	char out[2];
// 	long long index = cube.flat_coord();
// 	in.seekg(index, std::ios::beg);
// 	// fseeko64(f, cube.flat_coord(), SEEK_SET);
// 	// char t[5] = fgets(out, 1, f);
// 	// std::cout << "t " << t << std::endl;
// 	in.read(out, 1);
// 	// in.seekg(-1 * (index + 1), std::ios::cur);
// 	// in.clear();
// 	return out[0];
// }

// void make_move_table()
// {
// 	char* table = (char*)malloc(sizeof(char) * HSIZEONE);
// 	for (unsigned int i = 0; i < HSIZEONE; i++)
// 	{
// 		if (i % (HSIZEONE / 1024) == 0)
// 		{
// 			std::cout << "back: " <<  i / (HSIZEONE / 1024) << " / 1024" << std::endl;
// 		}
// 		table[i] = get_move_for_cube(CoordCube(i));
// 	}
// 	write_to_file(table, PHASE_ONE_HEURISTIC_NAME, HSIZEONE);
// }
