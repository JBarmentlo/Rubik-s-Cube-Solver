#ifndef COORDCUBE_HPP
#define COORDCUBE_HPP

#include "utils.hpp"
#include "cubiecube_utils.hpp"
#include "move_tables.hpp"

class CoordCube
{
    private:

    public :

    int corner_orientation_coord;
    int edge_orientation_coord;
    int UD_slice_coord;
    
    
    CoordCube(int corner_orientation_coord = 0, int edge_orientation_coord = 0, int UD_slice_coord = 0);
    ~CoordCube(void);

    void    print(void);
    bool	operator==(const CoordCube &cube);
    void    set_solved(void);
    void    apply_move(int move);

};

CoordCube*       create_baby_from_move(CoordCube *mommy_cube, int move);


#endif
