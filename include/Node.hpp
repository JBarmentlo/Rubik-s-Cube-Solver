#ifndef NODE_HPP
#define NODE_HPP

#include <vector>
#include "CoordCube.hpp"
#include "cubiecube_utils.hpp"

using namespace std;

class Node
{
    private:

 
    public:
        int             g;
        int             h;
        int             f;
        CoordCube*    coordcube;

        Node(short g, short h, CoordCube* coordcube);
        ~Node(void);

        vector<Node*>       get_bebes();
        void                print();
        void                set_h(int h);
};


#endif