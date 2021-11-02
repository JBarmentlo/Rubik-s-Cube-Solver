#ifndef CUBUIECUBE_H
#define CUBUIECUBE_H

#include <iostream>
#include "define.hpp"
#include <cstring>

#include "utils.hpp"


// This struct can be used to define a cube state or a permutation.
// (because a cube state can be defined as a permutation applied to the solved cube state)
typedef struct 	cubiecube_s {
	corner_t	corner_positions[CORNER_NUM];
	char		corner_orientations[CORNER_NUM]; //  0, 1 , 2
	edge_t		edge_positions[EDGE_NUM];
	char		edge_orientations[EDGE_NUM]; //  0, 1
}				cubiecube_t;

static cubiecube_t homecube = {{URF, UFL, ULB, UBR, DFR, DLF, DBL, DRB}, {0, 0, 0, 0, 0, 0, 0, 0}, {UR, UF, UL, UB, DR, DF, DL, DB, FR, FL, BL, BR}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};


cubiecube_t* 	get_moves();
void			set_solved_cubiecube(cubiecube_t* cube);
void 			apply_move(cubiecube_t* cube, int move);
void 			apply_move(cubiecube_t* cube, cubiecube_t* move);
void			apply_move_corners(cubiecube_t* cube, cubiecube_t* move);
void			apply_move_edges(cubiecube_t* cube, cubiecube_t* move);


int				corner_orientation_coordinate_1(cubiecube_t* cube);
void			set_corner_orientation_coord_1(int coord, cubiecube_t* cube);

int				edge_orientation_coordinate_1(cubiecube_t* cube);
void			set_edge_orientation_coord_1(int coord, cubiecube_t* cube);

int				UD_slice_coordinate_1(cubiecube_t* cube);
void			set_UD_slice_coord_1(int coord, cubiecube_t* cube);

int				corner_permutation_coordinate_2(cubiecube_t* cube);
void			set_corner_permutation_coordinate_2(int index, cubiecube_t* cube);

int				edge_permutation_coordinate_2(cubiecube_t* cube);
void			set_edge_permutation_coordinate_2(int index, cubiecube_t* cube);

int				UD_slice_sorted_coordinate_2(cubiecube_t* cube);
void			set_UD_slice_sorted_coordinate_2(int index,cubiecube_t* cube);

bool			is_cubiecube_goal(cubiecube_t* cube);
void			print_coords_phase1(cubiecube_t* cube);
void			print_coords_phase2(cubiecube_t* cube);



// int 				get_inverse_move_number(int move);
// int				edge_permutation_coordinate(cubiecube_t* cube);
// cubiecube_t		create_cubie_with_corner_orientation_coord(int coord);
// cubiecube_t		create_cubie_with_edge_orientation_coord(int coord);
// cubiecube_t		create_cubie_with_UD_slice_coord(int coord);
// std::string 		corner_position_to_string(corner_t c);
// void 			print_corners(cubiecube_t* cude);
// void 			print_edges(cubiecube_t* cude);
// int				factorial(int n);
// // void			display(cubiecube_t* cube);


// int verify(cubiecube_t* cubiecube)
// {
//     int sum = 0, e, i, c;
//     int edgeCount[12] = {0};
//     int cornerCount[8] = {0};

//     for(e = 0; e < EDGE_COUNT; e++)
//         edgeCount[cubiecube->ep[e]]++;
//     for (i = 0; i < 12; i++)
//         if (edgeCount[i] != 1)
//             return -2;

//     for (i = 0; i < 12; i++)
//         sum += cubiecube->eo[i];
//     if (sum % 2 != 0)
//         return -3;

//     for(c = 0; c < CORNER_COUNT; c++)
//         cornerCount[cubiecube->cp[c]]++;
//     for (i = 0; i < 8; i++)
//         if (cornerCount[i] != 1)
//             return -4;// missing corners

//     sum = 0;
//     for (i = 0; i < 8; i++)
//         sum += cubiecube->co[i];
//     if (sum % 3 != 0)
//         return -5;// twisted corner

//     if ((edgeParity(cubiecube) ^ cornerParity(cubiecube)) != 0)
//         return -6;// parity error

//     return 0;// cube ok
// }


#endif
