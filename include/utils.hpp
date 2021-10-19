#ifndef UTILS_H
#define UTILS_H

#include "cubiecube_utils.hpp"
#include "define.hpp"
#include <string>
#include <vector>


int 			factorial(int n);
int 			binomial_coefficient(int n, int k);
// int				power_three(int n);
// int 			power_two(int n);
std::string 	corner_position_to_string(corner_t c);
std::string 	edge_position_to_string(edge_t e);
// int				get_corner_orientation_parity(cubiecube_t *cube);
bool 			is_ud_slice_edge(edge_t e);
// int				sum_cnk(int n0, int n1, int k);
// const bool*		allowed_moves(int previous_move);
void			rotate_left(int* arr, int l, int r);
void			rotate_left(edge_t* arr, int l, int r);
void			rotate_left(corner_t* arr, int l, int r);
void			rotate_right(int* arr, int l, int r);
void			rotate_right(edge_t* arr, int l, int r);
void			rotate_right(corner_t* arr, int l, int r);
// int*	        fill_table_with_value(int* table, int value, int size);


// // void			rotate_left_corner_array();
// // void			rotate_right_corner_array();
// // void			rotate_left_edge_array();
// // void			rotate_right_edge_array();
// float			get_table_filling(unsigned char *table);
// void			write_to_file(char* table, std::string filename, unsigned int size);



// void    print_array(int* arr, int size);
bool				is_allowed_move_phase2(int move);
std::vector<int>	create_random_shuffle(int moves);




#endif


