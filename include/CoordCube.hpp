#ifndef COORDCUBE_HPP
#define COORDCUBE_HPP

typedef struct  coord_cube_s
{
    int corner_orientation_coord;
    int edge_orientation_coord;
    int UD_slice_coord;

}               coord_cube_t;

coord_cube_t    create_baby_from_move(coord_cube_t mommy_cube, int move);
void            set_solved(coord_cube_t *cube);


#endif
