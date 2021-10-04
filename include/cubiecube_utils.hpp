#ifndef CUBUIECUBE_H
#define CUBUIECUBE_H

#include <iostream>
#include <cstdint>


#define FIRST_CORNER 	URF
#define LAST_CORNER 	DRB
#define FIRST_EDGE 		UR
#define LAST_EDGE 		BR

#define N_UD 			494 // Max values for coordinates
#define N_CORNER_ORI 	2186
#define N_EDGE_ORI 		2047
#define N_MOVES			18
#define N_BASIC_MOVES	6


typedef enum {
    URF, UFL, ULB, UBR, DFR, DLF, DBL, DRB
} corner_t;

inline corner_t operator++ (corner_t &d, int) {
	corner_t tmp = d;
    d = static_cast<corner_t>((static_cast<int>(d) + 1));
	return tmp;
}

inline corner_t operator-- (corner_t &d, int) {
	corner_t tmp = d;
    d = static_cast<corner_t>((static_cast<int>(d) - 1));
	return tmp;
}

typedef enum {
    UR, UF, UL, UB, DR, DF, DL, DB, FR, FL, BL, BR
} edge_t;

inline edge_t operator++ (edge_t &d, int) {
	edge_t tmp = d;
    d = static_cast<edge_t>((static_cast<int>(d) + 1));
	return tmp;
}

inline edge_t operator-- (edge_t &d, int) {
	edge_t tmp = d;
    d = static_cast<edge_t>((static_cast<int>(d) - 1));
	return tmp;
}

#define EDGE_NUM 12
#define CORNER_NUM 8




// This struct can be used to define a cube state or a permutation.
// (because a cube state can be defined as a permutation applied to the solved cube state)
struct cubiecube_s {
	corner_t	corner_positions[CORNER_NUM];
	char		corner_orientations[CORNER_NUM]; //  0, 1 , 2
	edge_t		edge_positions[EDGE_NUM];
	char		edge_orientations[EDGE_NUM]; //  0, 1
};
typedef struct cubiecube_s cubiecube_t;

static cubiecube_t homecube = {{URF, UFL, ULB, UBR, DFR, DLF, DBL, DRB}, {0, 0, 0, 0, 0, 0, 0, 0}, {UR, UF, UL, UB, DR, DF, DL, DB, FR, FL, BL, BR}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};


cubiecube_t* 	get_moves();
void 			apply_move(cubiecube_t* cube, int move);
void 			apply_move(cubiecube_t* cube, cubiecube_t* move);
void			apply_move_edges(cubiecube_t* cube, cubiecube_t* move);
void			apply_move_corners(cubiecube_t* cube, cubiecube_t* move);

cubiecube_t		create_cubie_with_corner_orientation_coord(int coord);
cubiecube_t		create_cubie_with_edge_orientation_coord(int coord);
cubiecube_t		create_cubie_with_UD_slice_coord(int coord);

// void			display(cubiecube_t* cube);

int				corner_orientation_coordinate(cubiecube_t* cube);
int				edge_orientation_coordinate(cubiecube_t* cube);
int				corner_permutation_coordinate(cubiecube_t* cube);
int				edge_permutation_coordinate(cubiecube_t* cube);
int				UD_slice_coordinate(cubiecube_t* cube);

int				phase2_edge_permutaion_coordinate(cubiecube_t* cube);

void			set_corner_orientation_coord(int coord, cubiecube_t* cube);
void			set_edge_orientation_coord(int coord, cubiecube_t* cube);
void			set_UD_slice_coord(int coord, cubiecube_t* cube);




std::string 	corner_position_to_string(corner_t c);



void 			print_corners(cubiecube_t* cude);
void 			print_edges(cubiecube_t* cude);
int				factorial(int n);


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
