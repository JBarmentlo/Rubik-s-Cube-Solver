#include "cubiecube.hpp"
#include <cstring>
#include <string>

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
}


void apply_move(cubiecube_t* cube, cubiecube_t* move)
{
	cubiecube_t			tmp;
	memcpy(&tmp, cube, sizeof(tmp));
	for (int i = 0; i < CORNER_NUM; i++)
	{
		cube->corner_positions[i] = tmp.corner_positions[move->corner_positions[i]];
		cube->corner_orientations[i] = (tmp.corner_orientations[move->corner_positions[i]] + move->corner_orientations[i]) % 3;
	}
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

int factorial(int n)
{
  return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
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
		out = out + (left * factorial(i)); // TODO put factorials up to 7 in a array for faster computation
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
			if (cube->corner_positions[j] > cube->corner_positions[i])
			{
				left = left + 1;
			}
		}
		out = out + (left * factorial(i)); // TODO put factorials up to 7 in a array for faster computation
	}

	return out;
}

std::string corner_position_to_string(corner_t c)
{
	if (c == 0)
	{
		return ("URF");
	}
	if (c == 1)
	{
		return ("UFL");
	}
	if (c == 2)
	{
		return ("ULB");
	}
	if (c == 3)
	{
		return ("UBR");
	}
	if (c == 4)
	{
		return ("DFR");
	}
	if (c == 5)
	{
		return ("DLF");
	}
	if (c == 6)
	{
		return ("DBL");
	}
	if (c == 7)
	{
		return ("DRB");
	}
	return ("");
}

void 			print_corners(cubiecube_t* cube)
{
	for (int i = 0; i < CORNER_NUM; i++)
	{
		std::cout << cube->corner_positions[i] << "\t";
	}
	std::cout << std::endl;
	for (int i = 0; i < CORNER_NUM; i++)
	{
		std::cout << (int)cube->corner_orientations[i] << "  \t";
	}
	std::cout << std::endl;
	std::cout << std::endl;
}
