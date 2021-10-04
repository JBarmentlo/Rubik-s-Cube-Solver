#ifndef UTILS_H
#define UTILS_H

#include "cubiecube_utils.hpp"


int 			factorial(int n);
int 			binomial_coefficient(int n, int k);
int				power_three(int n);
int 			power_two(int n);
std::string 	corner_position_to_string(corner_t c);
std::string 	edge_position_to_string(edge_t e);
int				get_corner_orientation_parity(cubiecube_t *cube);
bool 			is_ud_slice_edge(edge_t e);
int				sum_cnk(int n0, int n1, int k);
int**           read_raw_move_table(int coord_max, std::string filename);
// void			rotate_left_corner_array();
// void			rotate_right_corner_array();
// void			rotate_left_edge_array();
// void			rotate_right_edge_array();
#endif


