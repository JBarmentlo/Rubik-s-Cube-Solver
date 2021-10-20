#include "kociemba.hpp"
#include "CubieCube.hpp"

std::queue<int>     get_path_to_phase_one(std::vector<int> shuffle)
{
    CoordCube start(0);

	if (VERBOSE > 1)
    	{std::cout << "\n\nBEFORE SHUFFLE:" << std::endl;
    	start.print_coords_phase1();};

    for(auto move : shuffle)
    {
        start.apply_move_phase_one(move);
    }
	if (VERBOSE > 1)
		{std::cout << "\nAFTER SHUFFLE:" << std::endl;
		start.print_coords_phase1();};
	
    std::queue<int> path;

	if (phase_one_goal(start) == true)
		return (path);

    phase_one_solver(start, 0, &path);

    return(path);
}


std::queue<int>    get_path_to_phase_two(std::vector<int> shuffle, std::queue<int> path_to_phase_one)
{
    cubiecube_t cubie;
    set_solved_cubiecube(&cubie);

    for(int move : shuffle)
        apply_move(&cubie, move);

    while (not path_to_phase_one.empty())
    {
        apply_move(&cubie, path_to_phase_one.front());
        path_to_phase_one.pop();
    }
    CoordCube start(cubie);
    std::queue<int> *path_to_phase_two = new std::queue<int>;

    phase_two_solver(start, path_to_phase_two);
	// phase_two_solver_thread(start, path_to_phase_two);
	return (*path_to_phase_two);
}


void	test_result(std::vector<int> input_shuffle, std::vector<int> output_shuffle)
{
	cubiecube_t cubie;

	std::cout << "ENTERING TEST FUNCTION (all values should be equal to 0):" << std::endl;
	set_solved_cubiecube(&cubie);

	for(auto move : input_shuffle)
		apply_move(&cubie, move);

	for(auto move : output_shuffle)
		apply_move(&cubie, move);
	
	if (is_cubiecube_goal(&cubie) == true)
		std::cout << "**** ALL GOOD ****" << std::endl;
	else
		std::cout << "!!!!! ERROR !!!!!!" << std::endl;
	print_coords_after_phase2(&cubie);
}


std::vector<int>                kociemba(std::vector<int> input_shuffle)
{
    int total_path_length = 0;
	std::vector<int> final_solution;

	if (VERBOSE >= 1)
		{std::cout << "\nINPUT SHUFFLE:" << std::endl;
		for(auto move : input_shuffle)
			std::cout << moves_strings[move] << " ";};

    std::queue<int> path_to_phase_one = get_path_to_phase_one(input_shuffle);

    total_path_length += path_to_phase_one.size();

    std::queue<int> path_to_phase_two = get_path_to_phase_two(input_shuffle, path_to_phase_one);

    total_path_length += path_to_phase_two.size();


	if (VERBOSE >= 1 && path_to_phase_one.empty() == false)
    	{std::cout << "\n\nMOVES TO APPLY TO GET TO PHASE ONE:" << std::endl;};
	if (VERBOSE >= 1 && path_to_phase_one.empty() == true)
    	{std::cout << "\n\nNO NEED FOR A PHASE ONE" << std::endl;};
    while(not path_to_phase_one.empty())
    {
		if (VERBOSE >= 1)
        	{std::cout << moves_strings[path_to_phase_one.front()] << " ";};
		final_solution.push_back(path_to_phase_one.front());
        path_to_phase_one.pop();
    }

	if (VERBOSE >= 1 && path_to_phase_two.empty() == false)
    	{std::cout << "\n\nMOVES TO APPLY TO GET TO PHASE TWO:" << std::endl;};
	if (VERBOSE >= 1 && path_to_phase_two.empty() == true)
    	{std::cout << "\n\nNO NEED FOR A PHASE TWO" << std::endl;};
	while(not path_to_phase_two.empty())
    {
		if (VERBOSE >= 1)
		    {std::cout << moves_strings[path_to_phase_two.front()] << " ";};
		final_solution.push_back(path_to_phase_two.front());
        path_to_phase_two.pop();
    }

    std::cout << "\n\nTOTAL PATH LENGTH: " << final_solution.size() << "\n\n";
	
	test_result(input_shuffle, final_solution);

	return (final_solution);
}