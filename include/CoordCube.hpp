#ifndef COORDCUBE_HPP
#define COORDCUBE_HPP

class CoordCube
{
    private:

    public :

    int corner_orientation_coord;
    int edge_orientation_coord;
    int UD_slice_coord;
    
    
    CoordCube(void);
    ~CoordCube(void);

    void    print(void);
    bool	operator==(CoordCube &cube);
    // bool	operator==(const CoordCube &cube);


};

CoordCube*       create_baby_from_move(CoordCube *mommy_cube, int move);
void            set_solved(CoordCube *cube);

// bool	operator==(const CoordCube &cube1, const CoordCube &cube2);


#endif
