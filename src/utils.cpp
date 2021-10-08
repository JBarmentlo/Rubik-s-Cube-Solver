#include <string>
#include <cstring>

#include <fstream>
#include "utils.hpp"

int				factorial(int n)
{
	static int factorials[13] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800, 39916800, 479001600}; // FOR SPEED
  	return factorials[n];
};

int				binomial_coefficient(int n, int k)
{
	int s(1);
	int i(n);
	int	j(1);

	if (n < k)
	{
		return (0);
	}
	if (k > n / 2)
	{
		k = n - k; // Optimization
	}
	while(i != (n - k))
	{
		s = s * i;
		s = s / j;
		i = i - 1;
		j = j + 1;
	}
	return (s);
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

void			rotate_left(edge_t* arr, int l, int r)
{
	edge_t tmp = arr[l];

	for (int i = l; i < r; i++)
	{
		arr[i] = arr[i + 1];
	}
	arr[r] = tmp;
}

void			rotate_right(edge_t* arr, int l, int r)
{
	edge_t tmp = arr[r];

	for (int i = r; i > l; i--)
	{
		arr[i] = arr[i - 1];
	}
	arr[l] = tmp;
}

void			rotate_left(corner_t* arr, int l, int r)
{
	corner_t tmp = arr[l];

	for (int i = l; i < r; i++)
	{
		arr[i] = arr[i + 1];
	}
	arr[r] = tmp;
}

void			rotate_right(corner_t* arr, int l, int r)
{
	corner_t tmp = arr[r];

	for (int i = r; i > l; i--)
	{
		arr[i] = arr[i - 1];
	}
	arr[l] = tmp;
}


void 			print_array(int* arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		std::cout << arr[i] << ", ";
	}
	std::cout << std::endl;
}

inline unsigned char write_half_char_left(unsigned char dest, unsigned char value)
{
	dest = dest << 4;
	dest = dest >> 4;

	dest = dest + (value << 4);
	return dest;
}

inline unsigned char write_half_char_right(unsigned char dest, unsigned char value)
{
	dest = dest >> 4;
	dest = dest << 4;

	dest = dest + value;
	return dest;
}

inline unsigned char read_half_char_left(unsigned char dest)
{
	dest = dest >> 4;
	return dest;
}

inline unsigned char read_half_char_right(unsigned char dest)
{
	dest = dest << 4;
	dest = dest >> 4;
	return dest;
}


int*			fill_table_with_value(int* table, int value, int size)
{
	for (int i = 0; i < size; i++)
	{
		table[i] = value;
	}
	return (table);
}

float			get_table_filling(unsigned char *table)
{
	unsigned int size =  N_EDGE_ORI * N_CORNER_ORI * N_UD;
	unsigned int full = 0;

	for (unsigned int i; i < size; i++)
	{
		if (read_half_char_table(table, i) != 15)
		{
			full = full + 1;
		}
	}
	return (float(full) / float(size));
}

void 			write_half_char_table(unsigned char *table, unsigned char value, unsigned int idx)
{
	int new_idx = idx / 2;
	int odd = idx % 2;
	if (value > 15)
		return;
	
	if (odd == 0)
	{
		table[new_idx] = write_half_char_right(table[new_idx], value);
	}
	else
	{
		table[new_idx] = write_half_char_left(table[new_idx], value);
	}
}

void 			fill_half_char_table(unsigned char *table, unsigned char value, unsigned int max_idx)
{
	std::cout << "FILLING " << max_idx << std::endl;
	for (unsigned int i = 0; i < max_idx / 2; i++)
	{
		table[i] = 0;
		table[i] = write_half_char_right(table[i], value);
		table[i] = write_half_char_left(table[i], value);
	}
}

unsigned char 	read_half_char_table(unsigned const char *table, unsigned int idx)
{
	unsigned char out = table[idx / 2];
	if (idx % 2 == 0)
	{
		return (read_half_char_right(out));
	}
	else
	{
		return (read_half_char_left(out));
	}
}

float			write_to_file(char* table, std::string filename);

