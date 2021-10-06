#include "Node.hpp"
#include <iostream>
#include <vector>


using namespace std;

Node::Node(int g, int h, CoordCube* coordcube)
{
    this->g         = g;
    this->h         = h;
    this->f         = this->g + this->h;
    this->coordcube = coordcube;

}

Node::~Node(void)
{
    std::cout << "Node deconstructor\n";
}

bool	f_sorting(Node *one, Node *two)
{
	return (one->f < two->f);
}


vector<Node*>    Node::get_bebes(g_function g_func, heuristic_function heuristic)
{
    vector<Node*>   bebes(N_MOVES);
    CoordCube*      baby_coordcube;
    int             baby_g;
    int             baby_h;

    for (int move = 0; move < N_MOVES; move++)
    {
        baby_coordcube = create_baby_from_move(this->coordcube, move);
        std::cout << "mommy move = " << this->coordcube->origin_move << std::endl;
        std::cout << "baby move = " << baby_coordcube->origin_move << "\n\n\n";
        baby_g = g_func(this->g);
        baby_h = heuristic(baby_coordcube);
        bebes[move] = new Node(baby_g, baby_h, baby_coordcube);
    }
    std::sort (bebes.begin(), bebes.end(), f_sorting);
    return (bebes);
}

void         Node::set_h(int new_h)
{
    this->h = new_h;
    this->f = this->g + this->h;
}

void         Node::set_g(int new_g)
{
    this->g = new_g;
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