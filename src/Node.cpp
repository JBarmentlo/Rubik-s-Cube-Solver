#include "Node.hpp"
#include <iostream>
#include <vector>


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
    // delete coordcube;
}

bool	f_sorting(Node *one, Node *two)
{
	return (one->f < two->f);
}


vector<Node*>    Node::get_bebes(int (*heuristic)(CoordCube*))
{
    vector<Node*>    bebes(N_MOVES);
    for (int move = 0; move < N_MOVES; move++)
    {
        bebes[move] = new Node(this->g + 1, 0, create_baby_from_move(this->coordcube, move));
        bebes[move]->set_h(heuristic(bebes[move]->coordcube));
    }
    std::sort (bebes.begin(), bebes.end(), f_sorting);
    return (bebes);
}

void                Node::set_h(int new_h)
{
    this->h = new_h;
    this->f = this->g + this->h;
}



void    Node::print(void)
{
    std::cout << "g = [" << this->g << "]\n";
    std::cout << "h = [" << this->h << "]\n";
    std::cout << "corner coord: [" << this->coordcube->corner_orientation_coord << "]\n";
    std::cout << "edge coord: [" << this->coordcube->edge_orientation_coord << "]\n";
    std::cout << "UD slice coord: [" << this->coordcube->UD_slice_coord << "]\n";
}