#include "CoordCube.hpp"


CoordCube::CoordCube(int corner_orientation_coord_1, int edge_orientation_coord_1, int UD_slice_coord_1)
{
    this->corner_orientation_coord_1 = corner_orientation_coord_1;
    this->edge_orientation_coord_1 = edge_orientation_coord_1;
    this->UD_slice_coord_1 = UD_slice_coord_1;
}

// CoordCube::CoordCube(int origin_move, int corner_orientation_coord_1, int edge_orientation_coord_1, int UD_slice_coord_1, int corner_permutation_coord, int edge_permutation_coord, int UD_slice2_coord)
// {
//     this->origin_move = origin_move;
//     //phase1:
//     this->corner_orientation_coord_1 = corner_orientation_coord_1;
//     this->edge_orientation_coord_1 = edge_orientation_coord_1;
//     this->UD_slice_coord_1 = UD_slice_coord_1;
//     //phase2:
//     this->corner_permutation_coord = corner_permutation_coord;
//     this->edge_permutation_coord = edge_permutation_coord;
//     this->UD_slice2_coord = UD_slice2_coord;
// }

CoordCube::CoordCube(unsigned int flat_coord_1)
{
    this->corner_orientation_coord_1 = (int)(flat_coord_1 / (N_EDGE_ORI_1 * N_UD_1));
    this->edge_orientation_coord_1 = (int)((flat_coord_1 % N_EDGE_ORI_1 * N_UD_1) / N_UD_1);
    this->UD_slice_coord_1 = (int)(flat_coord_1 % N_UD_1);
}

CoordCube::~CoordCube(void)
{
    // std::cout << "Deconstructing CoordCube\n";
}

// void        CoordCube::set_solved_phase1(void)
// {
//     this->corner_orientation_coord_1 = 0;
//     this->edge_orientation_coord_1 = 0;
//     this->UD_slice_coord_1 = 0; 
// }

// void        CoordCube::set_solved_phase2(void)
// {
//     this->corner_permutation_coord = 0;
//     this->edge_permutation_coord = 0;
//     this->UD_slice2_coord = 0;

// }

// void        CoordCube::set_solved(void)
// {
//     this->corner_orientation_coord_1 = 0;
// 	this->edge_orientation_coord_1 = 0;
// 	this->UD_slice_coord_1 = 0;
//     this->corner_permutation_coord = 0;
//     this->edge_permutation_coord = 0;
//     this->UD_slice2_coord = 0;
// }

unsigned int     CoordCube::flat_coord(void)
{
    return (this->corner_orientation_coord_1 * N_EDGE_ORI_1 * N_UD_1 + this->edge_orientation_coord_1 * N_UD_1 + this->UD_slice_coord_1);
}


void CoordCube::print_coords_phase1()
{
    std::cout << "corner_orientation coord 1: [" << this->corner_orientation_coord_1 << "]\n";
    std::cout << "edge_orientation coord 1:   [" << this->edge_orientation_coord_1 << "]\n";
    std::cout << "UD slice1 coord 1:          [" << this->UD_slice_coord_1 << "]\n";
}


// void CoordCube::print_coords_phase2()
// {
//     std::cout << "corner_permutation coord: [" << this->corner_permutation_coord << "]\n";
//     std::cout << "edge_permutation coord:   [" << this->edge_permutation_coord << "]\n";
//     std::cout << "UD slice2 coord:          [" << this->UD_slice2_coord << "]\n";
// }



// void CoordCube::print_all_coords()
// {
//     std::cout << "corner_orientation coord: [" << this->corner_orientation_coord_1 << "]\n";
//     std::cout << "edge_orientation coord:   [" << this->edge_orientation_coord_1 << "]\n";
//     std::cout << "UD slice1 coord:          [" << this->UD_slice_coord_1 << "]\n";
//     std::cout << "corner_permutation coord: [" << this->corner_permutation_coord << "]\n";
//     std::cout << "edge_permutation coord:   [" << this->edge_permutation_coord << "]\n";
//     std::cout << "UD slice2 coord:          [" << this->UD_slice2_coord << "]\n";
//     std::cout << "flat coord:               [" << this->flat_coord() << "]\n";

// }

// void CoordCube::print()
// {
//     std::cout << "corner_orientation coord: [" << this->corner_orientation_coord_1 << "]\n";
//     std::cout << "edge_orientation coord:   [" << this->edge_orientation_coord_1 << "]\n";
//     std::cout << "UD slice1 coord:          [" << this->UD_slice_coord_1 << "]\n";
//     std::cout << "corner_permutation coord: [" << this->corner_permutation_coord << "]\n";
//     std::cout << "edge_permutation coord:   [" << this->edge_permutation_coord << "]\n";
//     std::cout << "UD slice2 coord:          [" << this->UD_slice2_coord << "]\n";
//     std::cout << "flat coord:               [" << this->flat_coord() << "]\n";

// }

// bool  is_allowed_move_phase2(int move)
// {
//   if (is_allowed_quarter_turns[move % N_BASIC_MOVES] == false &&
//       move != ((move % N_BASIC_MOVES) + N_BASIC_MOVES))
//       return false;
//     return true;
// }

void    CoordCube::apply_move_phase_one(int move)
{
    static int** corner_orientation_table_1 = read_corner_orientation_move_table_1();
    static int** edge_orientation_table_1 = read_edge_orientation_move_table_1();
    static int** UD_slice_table_1 = read_UD_move_table_1();

    this->corner_orientation_coord_1 = corner_orientation_table_1[this->corner_orientation_coord_1][move];
    this->edge_orientation_coord_1 = edge_orientation_table_1[this->edge_orientation_coord_1][move];
    this->UD_slice_coord_1 = UD_slice_table_1[this->UD_slice_coord_1][move];
}


// void    CoordCube::apply_move_phase_two(int move)
// {
//     static int** corner_permutation_table = read_corner_permutation_move_table();
//     static int** edge_permutation_table = read_edge_permutation_move_table();
//     static int** UD_slice2_table = read_UD2_move_table();

//     this->corner_permutation_coord = corner_permutation_table[this->corner_permutation_coord][move];
//     this->edge_permutation_coord = edge_permutation_table[this->edge_permutation_coord][move];
//     this->UD_slice2_coord = UD_slice2_table[this->UD_slice2_coord][move];
// }


// void    CoordCube::set_coords_phase_two(int corner_permutation_coord, int edge_permutation_coord, int UD_slice2_coord)
// {
//     this->corner_permutation_coord = corner_permutation_coord;
//     this->edge_permutation_coord = edge_permutation_coord;
//     this->UD_slice2_coord = UD_slice2_coord;
// }



// bool	CoordCube::operator==(const CoordCube &cube)
// {
//     if (cube.corner_orientation_coord_1 == this->corner_orientation_coord_1)
//         return true;
//     return false;
// }


// CoordCube*    create_baby_from_move_phase_one(CoordCube* mommy_cube, int move)
// {
//     static int** corner_orientation_table = read_corner_orientation_move_table();
//     static int** edge_orientation_table = read_edge_orientation_move_table();
//     static int** UD_slice_table = read_UD_move_table();

//     CoordCube* bb_cube = new CoordCube(
//         move,
//         corner_orientation_table[mommy_cube->corner_orientation_coord_1][move],
//         edge_orientation_table[mommy_cube->edge_orientation_coord_1][move],
//         UD_slice_table[mommy_cube->UD_slice_coord_1][move]
//     );
//     return (bb_cube);
// }

CoordCube    CoordCube::create_baby_from_move_phase1(int move)
{
    static int** corner_orientation_table_1 = read_corner_orientation_move_table_1();
    static int** edge_orientation_table_1 = read_edge_orientation_move_table_1();
    static int** UD_slice_table_1 = read_UD_move_table_1();

    CoordCube bb_cube = CoordCube(
        corner_orientation_table_1[this->corner_orientation_coord_1][move],
        edge_orientation_table_1[this->edge_orientation_coord_1][move],
        UD_slice_table_1[this->UD_slice_coord_1][move]
    ); // TODO: check if not calling other constructor
    return (bb_cube);
}

// CoordCube*    create_baby_from_move_phase_two(CoordCube* mommy_cube, int move)
// {
//     if (is_allowed_move_phase2(move) == false)
//         return (nullptr);

//     static int** corner_permutation_table = read_corner_permutation_move_table();
//     static int** edge_permutation_table = read_edge_permutation_move_table();
//     static int** UD_slice2_table = read_UD2_move_table();

//     CoordCube* bb_cube = new CoordCube(
//         move,
//         0,
//         0,
//         0,
//         corner_permutation_table[mommy_cube->corner_permutation_coord][move],
//         edge_permutation_table[mommy_cube->edge_permutation_coord][move],
//         UD_slice2_table[mommy_cube->UD_slice2_coord][move]
//     );

//     return (bb_cube);
// }

