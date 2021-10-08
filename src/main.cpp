#include "Node.hpp"
#include "ida.hpp"
#include "CoordCube.hpp"
#include "ida_utils.hpp"
#include "heuristics.hpp"
#include "heuristics_tables.hpp"
#include "Node.hpp"



// #include "cubiecube_utils.hpp"
// #include "CubieCube.hpp"
// #include "tests.hpp"
// #include "move_tables.hpp"
#include <fstream>
#include <string.h>
#include <stack>

#include "define.hpp"



int		main(void)
{
  
  CoordCube *test = new CoordCube();

  test->print();
  for (size_t i = 0; i < 10; i++)
  {
    test->apply_move_phase_one(i);
  }
  std::cout << "\n" << std::endl;
  test->print();
  Node *start = new Node(0, 0, test);
  
  stack<Node*> path;
  path = ida(start, phase_one_goal, phase_1_heuristic, g_plusone, create_baby_from_move_phase_one);
  std::cout << "path size = " << path.size() << "\n\n";
  Node* myresult;
  while (path.empty() == false)
  {
    myresult = path.top();
    std::cout << myresult->coordcube->origin_move << "--";
    path.pop();
  }
  std::cout << "\n" << std::endl;
  
  return 0;
}