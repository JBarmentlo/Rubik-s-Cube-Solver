#ifndef UTILS_H
#define UTILS_H

#include "cubiecube_utils.hpp"
#include "define.hpp"

#include <stdlib.h>
#include <string>
#include <vector>
#include <cstring>
#include <fstream>
#include <ctime>

typedef struct 	args_s {
	int			verbose; // 0, 1, 2
	bool		visu; // true to turn on the visual
}				args_t;



int 				factorial(int n);
int 				binomial_coefficient(int n, int k);
std::string 		corner_position_to_string(corner_t c);
std::string 		edge_position_to_string(edge_t e);
bool 				is_ud_slice_edge(edge_t e);
void				rotate_left(int* arr, int l, int r);
void				rotate_left(edge_t* arr, int l, int r);
void				rotate_left(corner_t* arr, int l, int r);
void				rotate_right(int* arr, int l, int r);
void				rotate_right(edge_t* arr, int l, int r);
void				rotate_right(corner_t* arr, int l, int r);
int*	        	fill_table_with_value(int* table, int value, int size);
bool				is_allowed_move_phase2(int move);
std::vector<int>	create_random_shuffle(int moves);
std::vector<char*>	ft_strsplit(char *string, const char delimiter);
bool				parse_arguments(int argc, char **argv, std::vector<int> *shuffle, args_t *arguments);
wchar_t*			from_char_to_vec(const char* filename);
wchar_t*			from_vec_to_arg(std::vector<int> vec);


// int				power_three(int n);
// int 				power_two(int n);
// int				get_corner_orientation_parity(cubiecube_t *cube);
// int				sum_cnk(int n0, int n1, int k);
// const bool*		allowed_moves(int previous_move);
// float			get_table_filling(unsigned char *table);
// void				write_to_file(char* table, std::string filename, unsigned int size);
// void    			print_array(int* arr, int size);



#endif


