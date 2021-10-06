#ifndef NODE_HPP
#define NODE_HPP

#include <vector>
#include "CoordCube.hpp"
#include "cubiecube_utils.hpp"
#include <algorithm>

typedef int (*heuristic_function)(CoordCube*);
typedef int (*g_function)(int g);



using namespace std;

class Node
{
    private:

 
    public:

        CoordCube*      coordcube;
        int             g;
        int             h;
        int             f;

        Node(int g, int h, CoordCube* coordcube);
        ~Node(void);

        vector<Node*>       get_bebes(g_function g_func, heuristic_function heuristic);
        void                print();
        void                set_h(int h);
        void                set_g(int g);

};


#endif