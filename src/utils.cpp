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


bool 			is_ud_slice_edge(edge_t e)
{
	return (e >=  FR);
};

void			rotate_left(int* arr, int l, int r)
{
	int tmp = arr[l];

	for (int i = l; i < r; i++)
	{
		arr[i] = arr[i + 1];
	}
	arr[r] = tmp;
};

void			rotate_right(int* arr, int l, int r)
{
	int tmp = arr[r];

	for (int i = r; i > l; i--)
	{
		arr[i] = arr[i - 1];
	}
	arr[l] = tmp;
};

void			rotate_left(edge_t* arr, int l, int r)
{
	edge_t tmp = arr[l];

	for (int i = l; i < r; i++)
	{
		arr[i] = arr[i + 1];
	}
	arr[r] = tmp;
};

void			rotate_right(edge_t* arr, int l, int r)
{
	edge_t tmp = arr[r];

	for (int i = r; i > l; i--)
	{
		arr[i] = arr[i - 1];
	}
	arr[l] = tmp;
};

void			rotate_left(corner_t* arr, int l, int r)
{
	corner_t tmp = arr[l];

	for (int i = l; i < r; i++)
	{
		arr[i] = arr[i + 1];
	}
	arr[r] = tmp;
};

void			rotate_right(corner_t* arr, int l, int r)
{
	corner_t tmp = arr[r];

	for (int i = r; i > l; i--)
	{
		arr[i] = arr[i - 1];
	}
	arr[l] = tmp;
};


int*			fill_table_with_value(int* table, int value, int size)
{
	for (int i = 0; i < size; i++)
	{
		table[i] = value;
	}
	return (table);
};

bool  is_allowed_move_phase2(int move)
{
	if (is_allowed_quarter_turns[move % N_BASIC_MOVES] == true)
		return true;
	if (move < 6 or move > 11)
		return false;
    return true;
};


std::vector<int>	create_random_shuffle(int moves)
{
	std::vector<int> shuffle(moves);
	int move;
	std::srand((unsigned) time(0));

	for (int i = 0; i < moves; i++)
	{
		move = std::rand() % N_MOVES;
		shuffle[i] = move;
	}
	return (shuffle);
};


std::vector<char*>		ft_strsplit(char *string, const char delimiter)
{
	std::vector<char*> v;
	char* chars_array = strtok(string, " ");

	while(chars_array)
	{
		v.push_back(chars_array);
		chars_array = strtok(NULL, " ");
	}
	return(v);
};

bool	check_real_atoi(char *arg)
{
	int i = 0;
	while (arg[i] != '\0')
		{
			if (isdigit(arg[i]) == false)
				return (false);
			i++;
		}
	return (true);
}

wchar_t*			from_char_to_vec(const char* filename)
{
	wchar_t* arg;
	int i;

	arg = (wchar_t *)malloc(sizeof(wchar_t) * (strlen(filename) + 1));

	for (i = 0; i < strlen(filename); i++)
	{
		arg[i] = filename[i];
	}
	arg[i] = '\0';
	return arg;
}


wchar_t*			from_vec_to_arg(std::vector<int> vec)
{
	wchar_t* arg;

	arg = (wchar_t *)malloc(sizeof(wchar_t) * (vec.size() * 3) + 1);
	int i = 0;
	for (int j = 0; j < vec.size(); j++)
	{
		int nb = vec[j];
		for (char c: moves_strings[nb])
		{
			arg[i] = c;
			i += 1;
		}
		if (j + 1 < vec.size())
		{
			arg[i] = ' ';
			i += 1;
		}
	}
	arg[i] = '\0';
	return arg;

}


bool	parse_arguments(int argc, char **argv, std::vector<int> *shuffle, args_t *arguments)
{
	arguments->visu = false;
	arguments->verbose = 0;
	if (argc <= 1 or argc > 5)
	{
		std::cout << USAGE;
		return (false);
	}
	for (int i = 1; i < argc; i++)
	{
		if (strcmp("--verbose", argv[i]) == 0 and (i + 1) < argc)
		{
			i += 1;
			arguments->verbose = atoi(argv[i]);
			if (check_real_atoi(argv[i]) == false or arguments->verbose < 0 or arguments->verbose > 2)
			{
				std::cout << USAGE;
				return (false);
			}
			
		}
		else if (strcmp("--visu", argv[i]) == 0 and (i + 1) < argc)
		{
			arguments->visu = true;
		}
		else
		{
			int moves = atoi(argv[i]);

			if (moves == 0 and argv[i][0] != '0')
			{
				std::vector<char*> v = ft_strsplit(argv[i], ' ');
				for(auto word : v)
				{
					if (moves_numbers.find(word) == moves_numbers.end())
					{
						std::cout << USAGE;
						return (false);
					}
					shuffle->push_back(moves_numbers[word]);
				}
				return (true);
			}
			if (check_real_atoi(argv[i]) == false)
			{
				std::cout << USAGE;
				return (false);
			}
			*shuffle = create_random_shuffle(moves);
		}

	}
	return (true);
};




// int				get_corner_orientation_parity(cubiecube_t *cube) // THIS SHOULD RETURN 0 IF THE CUBE IS VALID (SOLVABLE)
// {
// 	int out(0);
// 	for (corner_t i = URF; i <= DRB; i++)
// 	{
// 		out = out + cube->corner_orientations[i];
// 	}
// 	return (out);
// }


// int				sum_cnk(int n0, int n1, int k)
// {
// 	// Sun of binomial coefs for C(n0, k) to C(n1, k) included
// 	return (binomial_coefficient(n1 + 1, k + 1) - binomial_coefficient(n0, k + 1));
// }

// const bool*		allowed_moves(int previous_move)
// {
// 	static const bool*			allowed_moves[6];
// 	static bool 			first = true;

// 	static const bool		allowed_moves_1[18] =  {false, true, true, true, true, true, false, true, true, true, true, true, false, true, true, true, true, true};

// 	static const bool		allowed_moves_2[18] =  {true, false, true, true, true, true,
// 													true, false, true, true, true, true, 
// 													true, false, true, true, true, true};

// 	static const bool		allowed_moves_3[18] =  {true, true, false, true, true, true,
// 													true, true, false, true, true, true, 
// 													true, true, false, true, true, true};

// 	static const bool		allowed_moves_4[18] =  {true, true, true, false, true, true,
// 													true, true, true, false, true, true, 
// 													true, true, true, false, true, true};

// 	static const bool		allowed_moves_5[18] =  {true, true, true, true, false, true,
// 													true, true, true, true, false, true, 
// 													true, true, true, true, false, true};

// 	static const bool		allowed_moves_6[18] =  {true, true, true, true, true, false,
// 													true, true, true, true, true, false, 
// 													true, true, true, true, true, false};


// 	if (first)
// 	{
// 		allowed_moves[0] = allowed_moves_1;
// 		allowed_moves[1] = allowed_moves_2;
// 		allowed_moves[2] = allowed_moves_3;
// 		allowed_moves[3] = allowed_moves_4;
// 		allowed_moves[4] = allowed_moves_5;
// 		allowed_moves[5] = allowed_moves_6;
// 		std::cout <<  "YEP" << std::endl;
// 	}
// 	first = false;

// 	return allowed_moves[previous_move % 6]; // TODO: TEST THIS
// }

// Rotate array to the lesft left between l and r. r is included.


// void 			print_array(int* arr, int size)
// {
// 	for (int i = 0; i < size; i++)
// 	{
// 		std::cout << arr[i] << ", ";
// 	}
// 	std::cout << std::endl;
// }


// void			write_to_file(char* table, std::string filename, unsigned int size)
// {
// 	std::cout << "Writing table to file: " << filename << std::endl;
// 	std::ofstream out1(filename, std::ios_base::binary);
// 	out1.write(table, sizeof(char) * size);
// 	std::cout << "Done writing " << std::endl;
// }




// int				power_three(int n)
// {
// 	static int powers[10] = {1, 3, 9, 27, 81, 243, 729, 2187, 6561, 19683}; // FOR SPEED
//   	return powers[n];
// };

// int				power_two(int n)
// {
// 	static int powers[15] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384}; // FOR SPEED
//   	return powers[n];
// };
