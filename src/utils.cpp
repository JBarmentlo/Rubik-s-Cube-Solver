#include <string>
#include "cubiecube.hpp"

int				factorial(int n)
{
	static int factorials[12] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800, 39916800}; // FOR SPEED
  	return factorials[n];
};

int				binomial_coefficient(int n, int k)
{
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