#ifndef UTILS_H
#define UTILS_H

int factorial(int n);
int binomial_coefficient(int n, int k);
int	power_three(int n);
int power_two(int n);
std::string 	corner_position_to_string(corner_t c);
std::string 	edge_position_to_string(edge_t e);
int		get_corner_orientation_parity(cubiecube_t *cube);
bool is_ud_slice_edge(edge_t e);


#endif


