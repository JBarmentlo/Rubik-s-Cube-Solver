#include "CoordCube.hpp"
#include "utils.hpp"
#include "cubiecube_utils.hpp"

int**    get_raw_table(int size, std::string filename)
{
    int** raw_table = read_raw_move_table(size, filename);
    
    return (raw_table);
}


CoordCube::CoordCube(int corner_orientation, int edge_orientation, int UD_slice)
{
    this->corner_orientation_coord = corner_orientation;
    this->edge_orientation_coord = edge_orientation;
    this->UD_slice_coord = UD_slice;
}


CoordCube::~CoordCube(void)
{
    // std::cout << "Deconstructing CoordCube\n";
}

void        CoordCube::set_solved(void)
{
    this->corner_orientation_coord = 0;
	this->edge_orientation_coord = 0;
	this->UD_slice_coord = 0;   
}


void    CoordCube::print(void)
{
    std::cout << "corner coord: [" << this->corner_orientation_coord << "]\n";
    std::cout << "edge coord: [" << this->edge_orientation_coord << "]\n";
    std::cout << "UD slice coord: [" << this->UD_slice_coord << "]\n";
}


bool	CoordCube::operator==(const CoordCube &cube)
{
    if (cube.corner_orientation_coord == this->corner_orientation_coord)
		return true;
    return false;
}

void    CoordCube::apply_move(int move)
{
    static int** corner_orientation_table = get_raw_table(N_CORNER_ORI, CORNER_ORI_NAME);
    static int** edge_orientation_table = get_raw_table(N_EDGE_ORI, EDGE_ORI_NAME);
    static int** UD_slice_table = get_raw_table(N_UD, UD_SLICE_NAME);


    this->corner_orientation_coord = corner_orientation_table[this->corner_orientation_coord][move];
    this->edge_orientation_coord = edge_orientation_table[this->edge_orientation_coord][move];
    this->UD_slice_coord = UD_slice_table[this->UD_slice_coord][move];
}


CoordCube*    create_baby_from_move(CoordCube* mommy_cube, int move)
{
    static int** corner_orientation_table = get_raw_table(N_CORNER_ORI, CORNER_ORI_NAME);
    static int** edge_orientation_table = get_raw_table(N_EDGE_ORI, EDGE_ORI_NAME);
    static int** UD_slice_table = get_raw_table(N_UD, UD_SLICE_NAME);

    CoordCube* bb_cube = new CoordCube(
            corner_orientation_table[mommy_cube->corner_orientation_coord][move],
            edge_orientation_table[mommy_cube->edge_orientation_coord][move],
            UD_slice_table[mommy_cube->UD_slice_coord][move]
    );
    
    return (bb_cube);
}

