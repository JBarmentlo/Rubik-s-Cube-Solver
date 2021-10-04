#include "Node.hpp"
#include <iostream>
#include <vector>
#include "cubiecube_utils.hpp"

using namespace std;

Node::Node(short g, short h, CoordCube* coordcube)
{
    this->g = g;
    this->h = h;
    this->f = g + h;
    this->coordcube = coordcube;
}

Node::~Node(void)
{
    std::cout << "Node deconstructor\n";
    // delete data;
}

vector<Node*> Node::get_bebes()
{
    vector<Node*> bebes(N_MOVES);
    for (int move = 0; move < N_MOVES; move++)
    {
        bebes[move] = new Node(this->g + 1, 0, create_baby_from_move(this->coordcube, move));
    }
    return (bebes);
}


void    Node::print(void)
{
    std::cout << "g = [" << this->g << "]\n";
    std::cout << "h = [" << this->h << "]\n";
    std::cout << "corner coord: [" << this->coordcube->corner_orientation_coord << "]\n";
    std::cout << "edge coord: [" << this->coordcube->edge_orientation_coord << "]\n";
    std::cout << "UD slice coord: [" << this->coordcube->UD_slice_coord << "]\n";
}