#ifndef UTILS_H
#define UTILS_H

#include "cubiecube_utils.hpp"
#include <string>

int 			factorial(int n);
int 			binomial_coefficient(int n, int k);
int				power_three(int n);
int 			power_two(int n);
std::string 	corner_position_to_string(corner_t c);
std::string 	edge_position_to_string(edge_t e);
int				get_corner_orientation_parity(cubiecube_t *cube);
bool 			is_ud_slice_edge(edge_t e);
int				sum_cnk(int n0, int n1, int k);
const bool*		allowed_moves(int previous_move);
void			rotate_left(int* arr, int l, int r);
void			rotate_left(edge_t* arr, int l, int r);
void			rotate_left(corner_t* arr, int l, int r);
void			rotate_right(int* arr, int l, int r);
void			rotate_right(edge_t* arr, int l, int r);
void			rotate_right(corner_t* arr, int l, int r);
int*	        fill_table_with_value(int* table, int value, int size);

void 			write_half_char_table(unsigned char *table, unsigned char value, unsigned int idx);
void 			fill_half_char_table(unsigned char *table, unsigned char value, unsigned int max_idx);
unsigned char 	read_half_char_table(unsigned const char *table, unsigned int idx);
// void			rotate_left_corner_array();
// void			rotate_right_corner_array();
// void			rotate_left_edge_array();
// void			rotate_right_edge_array();
float			get_table_filling(unsigned char *table);
float			write_to_file(char* table, std::string filename);



void    print_array(int* arr, int size);


#endif


