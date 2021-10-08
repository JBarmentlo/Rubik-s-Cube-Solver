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
#include <vector>

#include "define.hpp"



int		main(void)
{
  
  CoordCube *test = new CoordCube();
  CubieCube cubie;

  cubie.set_solved();
  for (size_t i = 0; i < 10; i++)
  {
    test->apply_move_phase_one(i);
    apply_move(&cubie.data, i);
  }
  std::cout << "\n" << std::endl;
  test->print();
  Node *start = new Node(0, 0, test);

  vector<int> path;
  
  path = ida(start, phase_one_goal, phase_1_heuristic, g_plusone, create_baby_from_move_phase_one);
  
  for (size_t i = 0; i < path.size(); i++)
  {
    std::cout << path[i] << "-";
  }

  std::cout << "\n" << std::endl;
  std::cout << "corner ori: [" << cubie.corner_ori_coord() << "]" << std::endl;
  std::cout << "edge ori: [" << cubie.edge_ori_coord() << "]" << std::endl;
  std::cout << "UD slice 1: [" << cubie.UD_coord() << "]" << std::endl;
  std::cout << "corner perm: [" << cubie.corner_perm_coord() << "]" << std::endl;
  std::cout << "edge perm: [" << cubie.edge_perm_coord() << "]" << std::endl;
  std::cout << "UD slice2: [" << cubie.UD_coord() << "]" << std::endl;

  for (size_t i = 1; i < path.size(); i++)
  {
    apply_move(&cubie.data, path[i]);
  }
  std::cout << "\n\n\n" << std::endl;
  std::cout << "corner ori: [" << cubie.corner_ori_coord() << "]" << std::endl;
  std::cout << "edge ori: [" << cubie.edge_ori_coord() << "]" << std::endl;
  std::cout << "UD slice 1: [" << cubie.UD_coord() << "]" << std::endl;
  std::cout << "corner perm: [" << cubie.corner_perm_coord() << "]" << std::endl;
  std::cout << "edge perm: [" << cubie.edge_perm_coord() << "]" << std::endl;
  std::cout << "UD slice2: [" << cubie.UD_coord() << "]" << std::endl;

  
  return 0;
}