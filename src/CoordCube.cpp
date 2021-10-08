#include "CoordCube.hpp"



CoordCube::CoordCube(int corner_orientation_coord, int edge_orientation_coord, int UD_slice_coord)
{
    this->corner_orientation_coord = corner_orientation_coord;
    this->edge_orientation_coord = edge_orientation_coord;
    this->UD_slice_coord = UD_slice_coord;
}

CoordCube::CoordCube(unsigned int flat_coord_1)
{
    this->corner_orientation_coord = (int)(flat_coord_1 / (N_EDGE_ORI * N_UD));
    this->edge_orientation_coord = (int)((flat_coord_1 % N_EDGE_ORI * N_UD) / N_UD);
    this->UD_slice_coord = (int)(flat_coord_1 % N_UD);
}

CoordCube::~CoordCube(void)
{
    // std::cout << "Deconstructing CoordCube\n";
}

void               CoordCube::set_solved(void)
{
    this->corner_orientation_coord = 0;
	this->edge_orientation_coord = 0;
	this->UD_slice_coord = 0;   
}

unsigned int     CoordCube::flat_coord(void)
{
    return (this->corner_orientation_coord * N_EDGE_ORI * N_UD + this->edge_orientation_coord * N_UD + this->UD_slice_coord);
}

// void    CoordCube::print(void)
// {
//     std::cout << "corner coord: [" << this->corner_orientation_coord << "]\n";
//     std::cout << "edge coord: [" << this->edge_orientation_coord << "]\n";
//     std::cout << "UD slice coord: [" << this->UD_slice_coord << "]\n";
// }


void    CoordCube::apply_move(int move)
{
    static int** corner_orientation_table = read_corner_orientation_move_table();
    static int** edge_orientation_table = read_edge_orientation_move_table();
    static int** UD_slice_table = read_UD_move_table();

    this->corner_orientation_coord = corner_orientation_table[this->corner_orientation_coord][move];
    this->edge_orientation_coord = edge_orientation_table[this->edge_orientation_coord][move];
    this->UD_slice_coord = UD_slice_table[this->UD_slice_coord][move];
}


bool	CoordCube::operator==(const CoordCube &cube)
{
    if (cube.corner_orientation_coord == this->corner_orientation_coord)
        return true;
    return false;
}


CoordCube*    create_baby_from_move(CoordCube* mommy_cube, int move)
{
    static int** corner_orientation_table = read_corner_orientation_move_table();
    static int** edge_orientation_table = read_edge_orientation_move_table();
    static int** UD_slice_table = read_UD_move_table();

    CoordCube* bb_cube = new CoordCube(
        corner_orientation_table[mommy_cube->corner_orientation_coord][move],
        edge_orientation_table[mommy_cube->edge_orientation_coord][move],
        UD_slice_table[mommy_cube->UD_slice_coord][move]
    );
    return (bb_cube);
}

CoordCube    CoordCube::create_baby_from_move_stack(int move)
{
    static int** corner_orientation_table = read_corner_orientation_move_table();
    static int** edge_orientation_table = read_edge_orientation_move_table();
    static int** UD_slice_table = read_UD_move_table();

    CoordCube bb_cube = CoordCube(
        corner_orientation_table[this->corner_orientation_coord][move],
        edge_orientation_table[this->edge_orientation_coord][move],
        UD_slice_table[this->UD_slice_coord][move]
    );
    return (bb_cube);
}

void    CoordCube::print(void)
{
    std::cout << "co   \t" << this->corner_orientation_coord << std::endl;
    std::cout << "eo   \t" << this->edge_orientation_coord << std::endl;
    std::cout << "ud   \t" << this->UD_slice_coord << std::endl;
    std::cout << "flat \t" <<  this->corner_orientation_coord * N_EDGE_ORI * N_UD + this->edge_orientation_coord * N_UD + this->UD_slice_coord << std::endl;
}

