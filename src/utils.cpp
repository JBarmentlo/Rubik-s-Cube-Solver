#include <string>
#include <cstring>

#include "cubiecube_utils.hpp"

int				factorial(int n)
{
	static int factorials[13] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800, 39916800, 479001600}; // FOR SPEED
  	return factorials[n];
};

int				binomial_coefficient(int n, int k)
{
	if (n < k)
	{
		return (0);
	}
	if (k < 0)
	{
		return (0);
	}
	return (factorial(n) / (factorial(k) * factorial(n - k)));
};

int				power_three(int n)
{
	static int powers[10] = {1, 3, 9, 27, 81, 243, 729, 2187, 6561, 19683}; // FOR SPEED
  	return powers[n];
};

int				power_two(int n)
{
	static int powers[15] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384}; // FOR SPEED
  	return powers[n];
};

std::string 	corner_position_to_string(corner_t c)
{

	std::string names[12] = {"URF", "UFL", "ULB", "UBR", "DFR", "DLF", "DBL", "DRB"};
	return names[c];
};

std::string 	edge_position_to_string(edge_t e)
{
	std::string names[12] = {"UR", "UF", "UL", "UB", "DR", "DF", "DL", "DB", "FR", "FL", "BL", "BR"};
	return names[e];
};

int				get_corner_orientation_parity(cubiecube_t *cube) // THIS SHOULD RETURN 0 IF THE CUBE IS VALID (SOLVABLE)
{
	int out(0);
	for (corner_t i = URF; i <= DRB; i++)
	{
		out = out + cube->corner_orientations[i];
	}
	return (out);
}

bool is_ud_slice_edge(edge_t e)
{
	return (e >=  FR);
}

int				sum_cnk(int n0, int n1, int k)
{
	// Sun of binomial coefs for C(n0, k) to C(n1, k) included
	return (binomial_coefficient(n1 + 1, k + 1) - binomial_coefficient(n0, k + 1));
}

const bool*			allowed_moves(int previous_move)
{
	static const bool*			allowed_moves[6];
	static bool 			first = true;

	static const bool		allowed_moves_1[18] =  {false, true, true, true, true, true, false, true, true, true, true, true, false, true, true, true, true, true};

	static const bool		allowed_moves_2[18] =  {true, false, true, true, true, true,
													true, false, true, true, true, true, 
													true, false, true, true, true, true};

	static const bool		allowed_moves_3[18] =  {true, true, false, true, true, true,
													true, true, false, true, true, true, 
													true, true, false, true, true, true};

	static const bool		allowed_moves_4[18] =  {true, true, true, false, true, true,
													true, true, true, false, true, true, 
													true, true, true, false, true, true};

	static const bool		allowed_moves_5[18] =  {true, true, true, true, false, true,
													true, true, true, true, false, true, 
													true, true, true, true, false, true};

	static const bool		allowed_moves_6[18] =  {true, true, true, true, true, false,
													true, true, true, true, true, false, 
													true, true, true, true, true, false};


	if (first)
	{
		allowed_moves[0] = allowed_moves_1;
		allowed_moves[1] = allowed_moves_2;
		allowed_moves[2] = allowed_moves_3;
		allowed_moves[3] = allowed_moves_4;
		allowed_moves[4] = allowed_moves_5;
		allowed_moves[5] = allowed_moves_6;
		std::cout <<  "YEP" << std::endl;
	}
	first = false;

	return allowed_moves[previous_move % 6]; // TODO: TEST THIS
}

// Rotate array to the lesft left between l and r. r is included.
void			rotate_left(int* arr, int l, int r)
{
	int tmp = arr[l];

	for (int i = l; i < r; i++)
	{
		arr[i] = arr[i + 1];
	}
	arr[r] = tmp;
}

void			rotate_right(int* arr, int l, int r)
{
	int tmp = arr[r];

	for (int i = r; i > l; i--)
	{
		arr[i] = arr[i - 1];
	}
	arr[l] = tmp;
}


void print_array(int* arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		std::cout << arr[i] << ", ";
	}
	std::cout << std::endl;
}
	
