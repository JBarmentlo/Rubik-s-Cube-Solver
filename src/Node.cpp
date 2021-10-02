#include "Node.hpp"
#include <iostream>
#include <vector>

using namespace std;

Node::Node(short g, short h, int something, char name)
{
    this->name = name; //temporary
    this->g = g;
    this->h = h;
    this->f = g + h;
    this->something = something;
    // this->bebes = NULL;
}

vector<Node*> Node::get_bebes()
{
    return (this->bebes); // temporary
}

Node::~Node(void)
{
    std::cout << "Node deconstructor\n";
    // delete something;
}

void        Node::print(void)
{
    std::cout << "Name = [" << this->name << "]\n";
    std::cout << "f = [" << this->f << "] and something = [" << this->something << "]\n";
    // std::cout << "Bebes:\n";
    // for(auto bebe : this->bebes)
    // {
        // std::cout << bebe->name << " ; ";
    // }


}