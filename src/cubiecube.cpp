#include "cubiecube.hpp"
#include <cstring>
#include <string>


void apply_move(cubiecube_t* cube, cubiecube_t* move)
{
	cubiecube_t			tmp;
	memcpy(&tmp, cube, sizeof(tmp));
	for (int i = 0; i < CORNER_NUM; i++)
	{
		cube->corner_positions[i] = tmp.corner_positions[move->corner_positions[i]];
		cube->corner_orientations[i] = (tmp.corner_orientations[move->corner_positions[i]] + move->corner_orientations[i]) % 3;
	}
	for (int i = 0; i < EDGE_NUM; i++)
	{
		cube->edge_positions[i] = tmp.edge_positions[move->edge_positions[i]];
		cube->edge_orientations[i] = (tmp.edge_orientations[move->edge_positions[i]] + move->edge_orientations[i]) % 3;
	}
}

cubiecube_t* get_moves()
{
	static  cubiecube_t	moves[18];
	static	bool		first = true;

	static const corner_t	corner_positions_U[8]  = { UBR, URF, UFL, ULB, DFR, DLF, DBL, DRB };
    static const char		corner_orientations_U[8]  = { 0, 0, 0, 0, 0, 0, 0, 0 };
    static const edge_t		edge_positions_U[12] = { UB, UR, UF, UL, DR, DF, DL, DB, FR, FL, BL, BR };
    static const char		edge_orientations_U[12] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

    static const corner_t	corner_positions_R[8]  = { DFR, UFL, ULB, URF, DRB, DLF, DBL, UBR };
    static const char		corner_orientations_R[8]  = { 2, 0, 0, 1, 1, 0, 0, 2 };
    static const edge_t		edge_positions_R[12] = { FR, UF, UL, UB, BR, DF, DL, DB, DR, FL, BL, UR };
    static const char		edge_orientations_R[12] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

    static const corner_t	corner_positions_F[8]  = { UFL, DLF, ULB, UBR, URF, DFR, DBL, DRB };
    static const char		corner_orientations_F[8]  = { 1, 2, 0, 0, 2, 1, 0, 0 };
    static const edge_t		edge_positions_F[12] = { UR, FL, UL, UB, DR, FR, DL, DB, UF, DF, BL, BR };
    static const char		edge_orientations_F[12] = { 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0 };

    static const corner_t	corner_positions_D[8]  = { URF, UFL, ULB, UBR, DLF, DBL, DRB, DFR };
    static const char		corner_orientations_D[8]  = { 0, 0, 0, 0, 0, 0, 0, 0 };
    static const edge_t		edge_positions_D[12] = { UR, UF, UL, UB, DF, DL, DB, DR, FR, FL, BL, BR };
    static const char		edge_orientations_D[12] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

    static const corner_t	corner_positions_L[8]  = { URF, ULB, DBL, UBR, DFR, UFL, DLF, DRB };
    static const char		corner_orientations_L[8]  = { 0, 1, 2, 0, 0, 2, 1, 0 };
    static const edge_t		edge_positions_L[12] = { UR, UF, BL, UB, DR, DF, FL, DB, FR, UL, DL, BR };
    static const char		edge_orientations_L[12] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

    static const corner_t	corner_positions_B[8]  = { URF, UFL, UBR, DRB, DFR, DLF, ULB, DBL };
    static const char		corner_orientations_B[8]  = { 0, 0, 1, 2, 0, 0, 2, 1 };
    static const edge_t		edge_positions_B[12] = { UR, UF, UL, BR, DR, DF, DL, BL, FR, FL, UB, DB };
    static const char		edge_orientations_B[12] = { 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1 };

	if (first) {
        memcpy(moves[0].corner_positions, corner_positions_U, sizeof(corner_positions_U));
        memcpy(moves[0].corner_orientations, corner_orientations_U, sizeof(corner_orientations_U));
        memcpy(moves[0].edge_positions, edge_positions_U, sizeof(edge_positions_U));
        memcpy(moves[0].edge_orientations, edge_orientations_U, sizeof(edge_orientations_U));

        memcpy(moves[1].corner_positions, corner_positions_R, sizeof(corner_positions_R));
        memcpy(moves[1].corner_orientations, corner_orientations_R, sizeof(corner_orientations_R));
        memcpy(moves[1].edge_positions, edge_positions_R, sizeof(edge_positions_R));
        memcpy(moves[1].edge_orientations, edge_orientations_R, sizeof(edge_orientations_R));

        memcpy(moves[2].corner_positions, corner_positions_F, sizeof(corner_positions_F));
        memcpy(moves[2].corner_orientations, corner_orientations_F, sizeof(corner_orientations_F));
        memcpy(moves[2].edge_positions, edge_positions_F, sizeof(edge_positions_F));
        memcpy(moves[2].edge_orientations, edge_orientations_F, sizeof(edge_orientations_F));

        memcpy(moves[3].corner_positions, corner_positions_D, sizeof(corner_positions_D));
        memcpy(moves[3].corner_orientations, corner_orientations_D, sizeof(corner_orientations_D));
        memcpy(moves[3].edge_positions, edge_positions_D, sizeof(edge_positions_D));
        memcpy(moves[3].edge_orientations, edge_orientations_D, sizeof(edge_orientations_D));

        memcpy(moves[4].corner_positions, corner_positions_L, sizeof(corner_positions_L));
        memcpy(moves[4].corner_orientations, corner_orientations_L, sizeof(corner_orientations_L));
        memcpy(moves[4].edge_positions, edge_positions_L, sizeof(edge_positions_L));
        memcpy(moves[4].edge_orientations, edge_orientations_L, sizeof(edge_orientations_L));

        memcpy(moves[5].corner_positions, corner_positions_B, sizeof(corner_positions_B));
        memcpy(moves[5].corner_orientations, corner_orientations_B, sizeof(corner_orientations_B));
        memcpy(moves[5].edge_positions, edge_positions_B, sizeof(edge_positions_B));
        memcpy(moves[5].edge_orientations, edge_orientations_B, sizeof(edge_orientations_B));

		for (int i = 0; i < 6; i++)
		{
			memcpy(&moves[i + 6], &moves[i], sizeof(moves[i]));
			apply_move(&moves[i + 6], &moves[i]);
			memcpy(&moves[i + 12], &moves[i + 6], sizeof(moves[i]));
			apply_move(&moves[i + 12], &moves[i]);
		}
    }

	first = false;
	return moves;
}


void apply_move(cubiecube_t* cube, int move)
{
	static cubiecube_t* moves = get_moves();
	cubiecube_t			tmp;
	memcpy(&tmp, cube, sizeof(tmp));

	cubiecube_t move_cube = moves[move];
	for (int i = 0; i < CORNER_NUM; i++)
	{
		cube->corner_positions[i] = tmp.corner_positions[move_cube.corner_positions[i]];
		cube->corner_orientations[i] = (tmp.corner_orientations[move_cube.corner_positions[i]] + move_cube.corner_orientations[i]) % 3;
	}
	for (int i = 0; i < EDGE_NUM; i++)
	{
		cube->edge_positions[i] = tmp.edge_positions[move_cube.edge_positions[i]];
		cube->edge_orientations[i] = (tmp.edge_orientations[move_cube.edge_positions[i]] + move_cube.edge_orientations[i]) % 3;
	}
}




int factorial(int n)
{
	static int factorials[12] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800, 39916800}; // FOR SPEED
  	return factorials[n];
}


int binomial_coefficient(int n, int k)
{
	return (factorial(n) / (factorial(k) * factorial(n - k)));
}



int				corner_orientation_coordinate(cubiecube_t* cube)
{
	int out(0);

	for (int i = CORNER_NUM - 1; i > 0; i--) // This loop intentionnaly does not include the first corner orientation http://kociemba.org/cube.htm Coordinate level
	{
		out = out * 3 + cube->corner_orientations[i]; // TODO put powers up to 7 in a array for faster computation
	}

	return out;
};


int				edge_orientation_coordinate(cubiecube_t* cube)
{
	int out(0);

	for (int i = EDGE_NUM - 1; i > 0; i--) // This loop intentionnaly does not include the first edge orientation http://kociemba.org/cube.htm Coordinate level
	{
		out = out * 2 + cube->edge_orientations[i];
	}

	return out;
}


int				corner_permutation_coordinate(cubiecube_t* cube)
{
	int out(0);
	int left;

	for (int i = 0; i < CORNER_NUM; i++)
	{
		left = 0;
		for (int j = 0; j < i; j++)
		{
			if (cube->corner_positions[j] > cube->corner_positions[i])
			{
				left = left + 1;
			}
		}
		out = out + (left * factorial(i));
	}

	return out;
};



int				edge_permutation_coordinate(cubiecube_t* cube)
{
	int out(0);
	int left;

	for (int i = 0; i < EDGE_NUM; i++)
	{
		left = 0;
		for (int j = 0; j < i; j++)
		{
			if (cube->edge_positions[j] > cube->edge_positions[i])
			{
				left = left + 1;
			}
		}
		out = out + (left * factorial(i));
	}

	return out;
}



int				UD_slice_coordinate(cubiecube_t* cube)
{
	int		occupied[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int		k[12];
	int		out(0);

	for (int i = 8; i < EDGE_NUM; i++) // we iterate over the UD slice edges
	{
		occupied[cube->edge_positions[i]] = 1;
	}
	for (int i = 0; i < EDGE_NUM; i++)
	{
		k[i] = 3;
		for (int j = i; j < EDGE_NUM; j++)
		{
			k[i] = k[i] - occupied[j];
		}
	}
	for (int i = 0; i < EDGE_NUM; i++)
	{
		if (k[i] != -1 && occupied[i] == 0)
		{
			out = out + binomial_coefficient(i, k[i]);
		}
	}
	return (out);
};

cubiecube_t		create_cubie_with_corner_coord(int coord)	
{
	int parity = 0;
	cubiecube_t cube;
	int corner;

	corner = DRB;
	memcpy(&cube, &homecube, sizeof(cube));
	while (corner >= URF)
	{
		parity = parity + (coord % 3);
		cube.corner_orientations[corner] = coord % 3;
		coord = coord / 3;
		std::cout << corner << std::endl;

		corner = (corner - 1);
	}
	parity = parity % 3;
	if (parity % 3 == 0)
	{
		cube.corner_orientations[DRB] = 0;
	}
	if (parity % 3 == 1)
	{
		cube.corner_orientations[DRB] = 2;
	}
	if (parity % 3 == 2)
	{
		cube.corner_orientations[DRB] = 1;
	}
	return (cube);
};








std::string corner_position_to_string(corner_t c)
{

	std::string names[12] = {"URF", "UFL", "ULB", "UBR", "DFR", "DLF", "DBL", "DRB"};
	return names[c];
}

std::string edge_position_to_string(edge_t e)
{
	std::string names[12] = {"UR", "UF", "UL", "UB", "DR", "DF", "DL", "DB", "FR", "FL", "BL", "BR"};
	return names[e];
}


void 			print_corners(cubiecube_t* cube)
{
	for (int i = 0; i < CORNER_NUM; i++)
	{
		std::cout << corner_position_to_string(cube->corner_positions[i]) << "\t";
	}
	std::cout << std::endl;
	for (int i = 0; i < CORNER_NUM; i++)
	{
		std::cout << (int)cube->corner_orientations[i] << "  \t";
	}
	std::cout << std::endl;
}

void 			print_edges(cubiecube_t* cube)
{
	for (int i = 0; i < EDGE_NUM; i++)
	{
		std::cout << edge_position_to_string(cube->edge_positions[i]) << "\t";
	}
	std::cout << std::endl;
	for (int i = 0; i < EDGE_NUM; i++)
	{
		std::cout << (int)cube->edge_orientations[i] << "  \t";
	}
	std::cout << std::endl;
}
