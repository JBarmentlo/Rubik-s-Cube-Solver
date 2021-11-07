#ifndef COORDCUBE_HPP
#define COORDCUBE_HPP

#include "cubiecube_utils.hpp"
#include "move_tables.hpp"

#include <vector>
#include <algorithm>


class CoordCube
{
    private:

    public :

    int origin_move;
    int g;
    int h;
    int f;

    int corner_orientation_coord_1;
    int edge_orientation_coord_1;
    int UD_slice_coord_1;
    
    int corner_permutation_coord_2;
    int edge_permutation_coord_2;
    int UD_slice_coord_2;
    

    CoordCube(int corner_orientation_coord_1, int edge_orientation_coord_1, int UD_slice_coord_1);
	CoordCube(unsigned int flat_coord_1);
	CoordCube(cubiecube_t cubie);
	CoordCube(int move, int corner_2, int edge_2, int UD_2);
    CoordCube();

    ~CoordCube(void);

	typedef int (*heuristic_function)(CoordCube);
	typedef int (*g_function)(int g);


	unsigned int     		flat_coord(void);
	unsigned int     		flat_coord_2_1(void);
	unsigned int     		flat_coord_2_2(void);

	void					set_solved();

    void    				apply_move_phase_one(int move);
    void    				apply_move_phase_two(int move);

	CoordCube				create_baby_from_move_phase1(int move); // ancienne fonction "from stack"
	CoordCube				create_baby_from_move_phase2(int move);
	std::vector<CoordCube>	get_babies_phase2(g_function g_func, heuristic_function heuristic);
	void					solver_init(void);

    void    				print_coords_phase1();
    void    				print_coords_phase2();
	void					print_all_coords();
    void    				print_phase_2();

};

bool						f_sorting(CoordCube one, CoordCube two);


#endif
