#ifndef COORDCUBE_HPP
#define COORDCUBE_HPP

// #include "utils.hpp"
// #include "cubiecube_utils.hpp"
#include "move_tables.hpp"
// #include <iostream>


class CoordCube
{
    private:

    public :

    // // Needed to check forbidden moves:
    // int origin_move;

    // // phase1:
    int corner_orientation_coord_1;
    int edge_orientation_coord_1;
    int UD_slice_coord_1;
    
    // // phase2:
    // int corner_permutation_coord;
    // int edge_permutation_coord;
    // int UD_slice2_coord;
    

	CoordCube(unsigned int flat_coord_1); // create cube from flat coordinate
    CoordCube(int corner_orientation_coord_1, int edge_orientation_coord_1, int UD_slice_coord_1);
    // CoordCube(int origin_move = NO_MOVE_APPLIED, int corner_orientation_coord = 0, int edge_orientation_coord = 0, int UD_slice_coord = 0, int corner_permutation_coord = 0, int edge_permutation_coord = 0, int UD_slice2_coord = 0);
    ~CoordCube(void);

    void    print_coords_phase1();
    // void    print_coords_phase2();
    // void    print();
    // void    print_all_coords(void);
    // // bool	operator==(const CoordCube &cube);
    // void    set_solved(void);
    // void    set_solved_phase1(void);
    // void    set_solved_phase2(void);

    void    apply_move_phase_one(int move);
    // void    apply_move_phase_two(int move);

    // void    set_coords_phase_two(int corner_permutation_coord, int edge_permutation_coord, int UD_slice2_coord);

	CoordCube			create_baby_from_move_phase1(int move); // ancienne fonction "from stack"
	unsigned int     	flat_coord(void);

};

// typedef CoordCube*       (*create_baby_function)(CoordCube *mommy_cube, int move);

// CoordCube*       create_baby_from_move_phase_one(CoordCube *mommy_cube, int move);
// CoordCube*       create_baby_from_move_phase_two(CoordCube *mommy_cube, int move);

// bool  is_allowed_move_phase2(int move);



#endif
