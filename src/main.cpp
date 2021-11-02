#include "kociemba.hpp"
#include "utils.hpp"
#include "define.hpp"
#include "deya_test.hpp"
#include "heuristics_tables.hpp"


#include <stdio.h>
#include <conio.h>
#include <Python.h>

void pypytonton()
{
	char filename[] = "../visu/code/test.py";
	FILE* fp;

	Py_Initialize();

	fp = _Py_fopen(filename, "r");
	PyRun_SimpleFile(fp, filename);
	// PyRun_SimpleString("import matplotlib");

	Py_Finalize();
	// if(!_getch()) _getch();

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
