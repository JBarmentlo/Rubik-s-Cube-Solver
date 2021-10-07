#include "Node.hpp"
#include "ida.hpp"
#include "CoordCube.hpp"
#include "ida_utils.hpp"
#include "heuristics.hpp"
#include "heuristics_tables.hpp"


// #include "cubiecube_utils.hpp"
// #include "CubieCube.hpp"
// #include "tests.hpp"
// #include "move_tables.hpp"
#include <fstream>
#include <string.h>

#include "define.hpp"


int		main(void)
{
  CoordCube *test = new CoordCube();

  test->print();
  for (size_t i = 0; i < 10; i++)
  {
    test->apply_move(i);
  }
  std::cout << "\n" << std::endl;
  test->print();
  Node *start = new Node(0, 0, test);

  ida(start, phase_one_goal, phase_1_heuristic, g_plusone);

  return 0;
}