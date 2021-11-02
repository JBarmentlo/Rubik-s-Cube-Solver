#include "CoordCube.hpp"


CoordCube::CoordCube(int corner_orientation_coord_1, int edge_orientation_coord_1, int UD_slice_coord_1)
{
    this->corner_orientation_coord_1 = corner_orientation_coord_1;
    this->edge_orientation_coord_1 = edge_orientation_coord_1;
    this->UD_slice_coord_1 = UD_slice_coord_1;
};


CoordCube::CoordCube(int move, int corner_2, int edge_2, int UD_2)
{
    this->origin_move = move;
    this->corner_permutation_coord_2 = corner_2;
    this->edge_permutation_coord_2 = edge_2;
    this->UD_slice_coord_2 = UD_2;
};


CoordCube::CoordCube(cubiecube_t cubie)
{
	this->corner_orientation_coord_1 = 0;
    this->edge_orientation_coord_1 = 0;
    this->UD_slice_coord_1 = 0;
    this->corner_permutation_coord_2 = corner_permutation_coordinate_2(&cubie);
    this->edge_permutation_coord_2 = edge_permutation_coordinate_2(&cubie);
    this->UD_slice_coord_2 = UD_slice_sorted_coordinate_2(&cubie);

};


CoordCube::CoordCube(void)
{
	this->corner_orientation_coord_1 = 0;
    this->edge_orientation_coord_1 = 0;
    this->UD_slice_coord_1 = 0;
    this->corner_permutation_coord_2 = 0;
    this->edge_permutation_coord_2 = 0;
    this->UD_slice_coord_2 = 0;
};


CoordCube::CoordCube(unsigned int flat_coord_1)
{
    this->corner_orientation_coord_1 = (int)(flat_coord_1 / (N_EDGE_ORI_1 * N_UD_1));
    this->edge_orientation_coord_1 = (int)((flat_coord_1 % N_EDGE_ORI_1 * N_UD_1) / N_UD_1);
    this->UD_slice_coord_1 = (int)(flat_coord_1 % N_UD_1);
};

CoordCube::~CoordCube(void)
{
    // std::cout << "Deconstructing CoordCube\n";
};


unsigned int     		CoordCube::flat_coord(void)
{
    return (this->corner_orientation_coord_1 * N_EDGE_ORI_1 * N_UD_1 + this->edge_orientation_coord_1 * N_UD_1 + this->UD_slice_coord_1);
};


void					CoordCube::set_solved(void)
{
	this->corner_orientation_coord_1 = 0;
    this->edge_orientation_coord_1 = 0;
    this->UD_slice_coord_1 = 0;
    this->corner_permutation_coord_2 = 0;
    this->edge_permutation_coord_2 = 0;
    this->UD_slice_coord_2 = 0;
}


void    				CoordCube::apply_move_phase_one(int move)
{
    static int** corner_orientation_table_1 = read_corner_orientation_move_table_1();
    static int** edge_orientation_table_1 = read_edge_orientation_move_table_1();
    static int** UD_slice_table_1 = read_UD_move_table_1();

    this->corner_orientation_coord_1 = corner_orientation_table_1[this->corner_orientation_coord_1][move];
    this->edge_orientation_coord_1 = edge_orientation_table_1[this->edge_orientation_coord_1][move];
    this->UD_slice_coord_1 = UD_slice_table_1[this->UD_slice_coord_1][move];
};


void    				CoordCube::apply_move_phase_two(int move)
{
    static int** corner_permutation_table2 = read_corner_permutation_move_table_2();
    static int** edge_permutation_table2 = read_edge_permutation_move_table_2();
    static int** UD_slice2_table2 = read_UD2_move_table_2();

    this->corner_permutation_coord_2 = corner_permutation_table2[this->corner_permutation_coord_2][move];
    this->edge_permutation_coord_2 = edge_permutation_table2[this->edge_permutation_coord_2][move];
    this->UD_slice_coord_2 = UD_slice2_table2[this->UD_slice_coord_2][move];
};


CoordCube    			CoordCube::create_baby_from_move_phase1(int move)
{
    static int** corner_orientation_table_1 = read_corner_orientation_move_table_1();
    static int** edge_orientation_table_1 = read_edge_orientation_move_table_1();
    static int** UD_slice_table_1 = read_UD_move_table_1();

    CoordCube bb_cube = CoordCube(
        corner_orientation_table_1[this->corner_orientation_coord_1][move],
        edge_orientation_table_1[this->edge_orientation_coord_1][move],
        UD_slice_table_1[this->UD_slice_coord_1][move]
    );
    return (bb_cube);
};



CoordCube    			CoordCube::create_baby_from_move_phase2(int move)
{
    static int** corner_permutation_table_2 = read_corner_permutation_move_table_2();
    static int** edge_permutation_table_2 = read_edge_permutation_move_table_2();
    static int** UD_slice2_table_2 = read_UD2_move_table_2();

    CoordCube bb_cube(
        move,
        corner_permutation_table_2[this->corner_permutation_coord_2][move],
        edge_permutation_table_2[this->edge_permutation_coord_2][move],
        UD_slice2_table_2[this->UD_slice_coord_2][move]
    );

    return (bb_cube);
};


std::vector<CoordCube>	CoordCube::get_babies_phase2(g_function g_func, heuristic_function heuristic)
{
    std::vector<CoordCube>	bebes(N_MOVES);
    CoordCube      			baby_coordcube;
    int             		nb_of_moves = 0;

    for (int move = 0; move < N_MOVES; move++)
    {
        if (((this->origin_move == NO_MOVE_APPLIED) or (move % N_BASIC_MOVES) != (this->origin_move % N_BASIC_MOVES)) && is_allowed_move_phase2(move))
        {
            baby_coordcube = this->create_baby_from_move_phase2(move);
			baby_coordcube.g = g_func(this->g);
			baby_coordcube.h = heuristic(baby_coordcube);
			baby_coordcube.f = baby_coordcube.g + baby_coordcube.h;
			bebes[nb_of_moves] = baby_coordcube;
			nb_of_moves += 1;
        }
    }
    bebes.resize(nb_of_moves);
    std::sort (bebes.begin(), bebes.end(), f_sorting);
    return (bebes);
};


void					CoordCube::solver_init(void)
{
	this->g = 0;
	this->h = 0;
	this->f = 0;
	this->origin_move = NO_MOVE_APPLIED;
};


bool					f_sorting(CoordCube one, CoordCube two)
{
	return (one.f < two.f);
};


void					CoordCube::print_coords_phase1()
{
    std::cout << "corner_orientation coord 1: [" << this->corner_orientation_coord_1 << "]\n";
    std::cout << "edge_orientation coord 1:   [" << this->edge_orientation_coord_1 << "]\n";
    std::cout << "UD slice1 coord 1:          [" << this->UD_slice_coord_1 << "]\n";
};


void					CoordCube::print_coords_phase2()
{
    std::cout << "corner_permutation_coord_2:  [" << this->corner_permutation_coord_2 << "]\n";
    std::cout << "edge_permutation_coord_2:    [" << this->edge_permutation_coord_2 << "]\n";
    std::cout << "UD_slice_coord_2:            [" << this->UD_slice_coord_2 << "]\n";
};


void					CoordCube::print_all_coords()
{
    std::cout << "corner_orientation coord: [" << this->corner_orientation_coord_1 << "]\n";
    std::cout << "edge_orientation coord:   [" << this->edge_orientation_coord_1 << "]\n";
    std::cout << "UD slice1 coord:          [" << this->UD_slice_coord_1 << "]\n";
    std::cout << "corner_permutation coord: [" << this->corner_permutation_coord_2 << "]\n";
    std::cout << "edge_permutation coord:   [" << this->edge_permutation_coord_2 << "]\n";
    std::cout << "UD slice2 coord:          [" << this->UD_slice_coord_2 << "]\n";
    std::cout << "flat coord:               [" << this->flat_coord() << "]\n";

};


void    				CoordCube::print_phase_2()
{
    std::cout << "origin move =                " << this->origin_move << std::endl;
    std::cout << "corner_permutation_coord_2 = " << this->corner_permutation_coord_2 << std::endl;
    std::cout << "edge_permutation_coord_2 =   " << this->edge_permutation_coord_2 << std::endl;
    std::cout << "UD_slice_coord_2 =           " << this->UD_slice_coord_2 << std::endl;
    std::cout << "g =  " << this->g << "   h = " << this->h << std::endl;
};


// bool	CoordCube::operator==(const CoordCube &cube)
// {
//     if (cube.corner_orientation_coord_1 == this->corner_orientation_coord_1)
//         return true;
//     return false;
// }