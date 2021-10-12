#include "kociemba.hpp"
#include "CubieCube.hpp"

std::queue<int>     get_path_to_phase_one(std::vector<int> shuffle)
{
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

    return(path);
}

void    get_path_to_phase_two(std::vector<int> shuffle, std::queue<int> path_to_phase_one)
{
    // cubiecube_t cubie;
    // set_solved_cubiecube(&cubie);
    CubieCube cubie;

    cubie.set_solved();

    for(int move : shuffle)
        apply_move(&cubie.data, move);

    std::cout << "\n\ncorner ori = " << corner_orientation_coordinate_1(&cubie.data) << std::endl;
    std::cout << "edge ori = " << edge_orientation_coordinate_1(&cubie.data) << std::endl;
    std::cout << "UD1 = " << UD_slice_coordinate_1(&cubie.data) << std::endl;

    // while (not path_to_phase_one.empty())
    // {
    //     apply_move(&cubie, path_to_phase_one.front());
    //     path_to_phase_one.pop();
    // }

}


void                kociemba(std::vector<int> shuffle)
{
    int total_path_length = 0;

    std::cout << "\nINPUT SHUFFLE:" << std::endl;
    for(auto move : shuffle)
    {
        std::cout << "[" << move << "]";
    }

    std::queue<int> path_to_phase_one = get_path_to_phase_one(shuffle);

    total_path_length += path_to_phase_one.size();

    get_path_to_phase_two(shuffle, path_to_phase_one);

    std::cout << "\nMOVES TO APPLY TO GET TO PHASE ONE" << std::endl;
    while(not path_to_phase_one.empty())
    {
        std::cout << "[" << path_to_phase_one.front() << "]";
        path_to_phase_one.pop();
    }
    std::cout << "\n\nTOTAL PATH LENGTH: " << total_path_length << "\n\n";


}