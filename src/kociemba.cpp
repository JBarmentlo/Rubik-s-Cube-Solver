#include "kociemba.hpp"

void    kociemba(std::vector<int> shuffle)
{
    int total_path_length = 0;

    std::cout << "\nINPUT SHUFFLE:" << std::endl;
    for(auto move : shuffle)
    {
        std::cout << "[" << move << "]";
    }
    CoordCube start(0);
    std::cout << "\n\nBEFORE SHUFFLE:" << std::endl;
    start.print_coords_phase1();
    for(auto move : shuffle)
    {
        start.apply_move_phase_one(move);
    }
    std::cout << "\nAFTER SHUFFLE:" << std::endl;
    start.print_coords_phase1();

    std::queue<int> path;
    phase_one_solver(start, 0, &path);

    total_path_length += path.size();
    std::cout << "\nMOVES TO APPLY TO GET TO PHASE ONE" << std::endl;
    while(not path.empty())
    {
        std::cout << "[" << path.front() << "]";
        path.pop();
    }
    std::cout << "\n\nTOTAL PATH LENGTH: " << total_path_length << "\n\n";


}