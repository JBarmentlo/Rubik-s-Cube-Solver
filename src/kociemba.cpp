#include "kociemba.hpp"
#include "CubieCube.hpp"
#include "deya_test.hpp"

std::queue<int>     get_path_to_phase_one(std::vector<int> shuffle, args_t args)
{
    CoordCube start(0);

    for(auto move : shuffle)
    {
        start.apply_move_phase_one(move);
    }
	
    std::queue<int> path;

	if (phase_one_goal(start) == true)
		return (path);

    phase_one_solver(start, 0, &path);

	// FREE the static tables:
	start.apply_move_phase_one(0);

    return(path);
}


std::stack<int>    get_path_to_phase_two(std::vector<int> shuffle, std::queue<int> path_to_phase_one, args_t args)
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

    std::stack<int> path_to_phase_two;

    phase_two_solver(start, &path_to_phase_two);

	return (path_to_phase_two);
}


std::vector<int>                kociemba(std::vector<int> input_shuffle, args_t args)
{
    int total_path_length = 0;
	std::vector<int> final_solution;

	if (args.verbose >= 1)
		{std::cout << "INPUT SHUFFLE:" << std::endl;
		for(auto move : input_shuffle)
			std::cout << moves_strings[move] << " ";};

    std::queue<int> path_to_phase_one = get_path_to_phase_one(input_shuffle, args);

    total_path_length += path_to_phase_one.size();

    std::stack<int> path_to_phase_two = get_path_to_phase_two(input_shuffle, path_to_phase_one, args);

    total_path_length += path_to_phase_two.size();

	if (args.verbose >= 2 && path_to_phase_one.empty() == false)
    	{std::cout << "\n\nMOVES TO APPLY TO GET TO PHASE ONE:" << std::endl;};
	if (args.verbose >= 2 && path_to_phase_one.empty() == true)
    	{std::cout << "\n\nNO NEED FOR A PHASE ONE" << std::endl;};
    while(not path_to_phase_one.empty())
    {
		if (args.verbose >= 2)
        	{std::cout << moves_strings[path_to_phase_one.front()] << " ";};
		final_solution.push_back(path_to_phase_one.front());
        path_to_phase_one.pop();
    }

	if (args.verbose >= 2 && path_to_phase_two.empty() == false)
    	{std::cout << "\n\nMOVES TO APPLY TO GET TO PHASE TWO:" << std::endl;};
	if (args.verbose >= 2 && path_to_phase_two.empty() == true)
    	{std::cout << "\n\nNO NEED FOR A PHASE TWO" << std::endl;};
	while(not path_to_phase_two.empty())
    {
		if (args.verbose >= 2)
		    {std::cout << moves_strings[path_to_phase_two.top()] << " ";};
		final_solution.push_back(path_to_phase_two.top());
        path_to_phase_two.pop();
    }

	if (args.verbose >= 1)
    {
		std::cout << "\n\nINPUT SHUFFLE LENGTH: " << input_shuffle.size() << "\n";
    	std::cout << "SOLUTION LENGTH:      " << final_solution.size() << "\n\n";
	}
	return (final_solution);
}