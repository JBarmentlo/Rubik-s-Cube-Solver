#include "kociemba.hpp"

void    kociemba(std::vector<int> shuffle)
{
    for(auto move : shuffle)
    {
        std::cout << "[" << move << "]" << std::endl;
    }
    CoordCube start(0);
    std::cout << "BEFORE:" << std::endl;
    start.print_coords_phase1();
    for(auto move : shuffle)
    {
        start.apply_move_phase_one(move);
    }
    std::cout << "AFTER:" << std::endl;
    start.print_coords_phase1();

}