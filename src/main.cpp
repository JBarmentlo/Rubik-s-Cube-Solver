#include "kociemba.hpp"
#include "utils.hpp"
#include "define.hpp"
#include "heuristics_tables.hpp"


#include <stdio.h>
#include <conio.h>
#include <Python.h>
#include <wchar.h>

void pypytonton(std::vector<int> shuffle, std::vector<int> solution)
{
	FILE* fp;
	const char* filename = "../src/visu.py";
	int argc = 2;
    wchar_t *argv[3];

    argc = 3;
	argv[0] = from_char_to_vec(filename);
	argv[1] = from_vec_to_arg(shuffle);
	argv[2] = from_vec_to_arg(solution);

	std::cout << "\n\nLAUNCHING VISUAL:" << std::endl;
    Py_Initialize();
    PySys_SetArgv(argc, argv);

	Py_Initialize();

	fp = _Py_fopen(filename, "r");
	PyRun_SimpleFile(fp, filename);

	Py_Finalize();
}


int	complete_process(int argc, char **argv)
{
	std::vector<int> shuffle;
	std::vector<int> solution;
	args_t arguments;

	if (parse_arguments(argc, argv, &shuffle, &arguments) == false)
		return (false);

	solution = kociemba(shuffle, arguments);
	if (arguments.verbose >= 1)
		{std::cout << "COMPLETE PATH TO SOLUTION:" << std::endl;}
	for(int i = 0; i < solution.size(); i++)
	{
		std::cout << moves_strings[solution[i]];
		if (i < solution.size() - 1)
			{std::cout << " ";};
	}
	if (arguments.visu == true)
		pypytonton(shuffle, solution);
	return (true);
}


int main(int argc, char **argv)
{
	if (complete_process(argc, argv) == true)
		return (true);
	return (false);
}
