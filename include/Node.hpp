#ifndef NODE_HPP
#define NODE_HPP

#include <vector>

using namespace std;

class Node
{
    private:

 
    public:
        char            name;
        int             g = 0;
        int             h = 0;
        int             f;
        int             something;
        vector<Node*>     bebes;

        Node(short g, short h, int something, char name);
        ~Node(void);


        vector<Node*>        get_bebes();
        void                print();

};


#endif