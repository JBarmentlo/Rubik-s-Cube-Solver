#include "CoordCube.hpp"
#include "utils.hpp"
#include "cubiecube_utils.hpp"


int**    get_raw_table(int size, std::string filename)
{
    int** raw_table = read_raw_move_table(size, filename);
    
    return (raw_table);
}


coord_cube_t    create_baby_from_move(coord_cube_t mommy_cube, int move)
{
    static int** corner_orientation_table = get_raw_table(N_CORNER_ORI, CORNER_ORI_NAME);
    static int** edge_orientation_table = get_raw_table(N_EDGE_ORI, EDGE_ORI_NAME);
    static int** UD_slice_table = get_raw_table(N_UD, UD_SLICE_NAME);

    coord_cube_t bb_cube;

    bb_cube.corner_orientation_coord = corner_orientation_table[mommy_cube.corner_orientation_coord][move];
    bb_cube.edge_orientation_coord = edge_orientation_table[mommy_cube.edge_orientation_coord][move];
    bb_cube.UD_slice_coord = UD_slice_table[mommy_cube.UD_slice_coord][move];
    
    return (bb_cube);
}

void        set_solved(coord_cube_t *cube)
{
    cube->corner_orientation_coord = 0;
	cube->edge_orientation_coord = 0;
	cube->UD_slice_coord = 0;
    
}