#ifndef CUBUIECUBE_H
#define CUBUIECUBE_H

#include <iostream>
#include <cstdint>

typedef enum {
    URF, UFL, ULB, UBR, DFR, DLF, DBL, DRB
} corner_t;


typedef enum {
    UR, UF, UL, UB, DR, DF, DL, DB, FR, FL, BL, BR
} edge_t;

#define EDGE_NUM 12
#define CORNER_NUM 8



class Cube  {
	public:
		virtual void display();
		virtual bool is_solved();
		virtual bool is_G1();
		virtual Cube get_bebes();

};

// This struct can be used to define a cube state or a permutation.
// (because a cube state can be defined as a permutation applied to the solved cube state)
struct CubieCube {
	corner_t	corner_positions[CORNER_NUM];
	char		corner_orientations[CORNER_NUM]; //  0, 1 , 2
	edge_t		edge_positions[EDGE_NUM];
	char		edge_orientations[EDGE_NUM]; //  0, 1
};
typedef struct CubieCube cubiecube_t;

static cubiecube_t homecube = {{URF, UFL, ULB, UBR, DFR, DLF, DBL, DRB}, {0, 0, 0, 0, 0, 0, 0, 0}, {UR, UF, UL, UB, DR, DF, DL, DB, FR, FL, BL, BR}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};


cubiecube_t* 	get_moves();
void 			apply_move(cubiecube_t* cube, int move);
void 			apply_move(cubiecube_t* cube, cubiecube_t* move);
// void			display(cubiecube_t* cube);

int				corner_orientation_coordinate(cubiecube_t* cube);
int				edge_orientation_coordinate(cubiecube_t* cube);
int				corner_permutation_coordinate(cubiecube_t* cube);
int				edge_permutation_coordinate(cubiecube_t* cube);
int				UD_slice_coordinate(cubiecube_t* cube);
std::string 	corner_position_to_string(corner_t c);
void 			print_corners(cubiecube_t* cude);
void 			print_edges(cubiecube_t* cude);
int				factorial(int n);


#endif
