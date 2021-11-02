#include "kociemba.hpp"
#include "utils.hpp"
#include "define.hpp"
#include "deya_test.hpp"
#include "heuristics_tables.hpp"


#include <stdio.h>
#include <conio.h>
#include <Python.h>
#include <wchar.h>

void pypytonton()
{
	FILE* fp;
	const char* filename = "../src/visu.py";
	int argc = 2;
    wchar_t *argv[3];

    argc = 3;
    argv[0] = L"../src/visu.py";
    argv[1] = L"F R U2 B' L' D'";
    argv[2] = L"D L B U2 R R2 F'";

    Py_SetProgramName(argv[0]);
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

	if (parse_arguments(argc, argv, &shuffle) == false)
		return (false);

	if (VERBOSE >= 1)
	{for (int move: shuffle)
		{
			std::cout << moves_strings[move] << " ";
		}
		std::cout << std::endl;};

	solution = kociemba(shuffle);
	if (VERBOSE >= 1)
		{std::cout << "COMPLETE PATH TO SOLUTION:" << std::endl;};
	for(int i = 0; i < solution.size(); i++)
	{
		std::cout << moves_strings[solution[i]];
		if (i < solution.size() - 1)
			{std::cout << " ";};
	}
	return (true);
}


int main(int argc, char **argv)
{
	// pypytonton();
	if (complete_process(argc, argv) == true)
		return (true);
	return (false);
}
