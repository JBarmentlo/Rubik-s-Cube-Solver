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

void  deyas_part(void)
{
  CoordCube *test = new CoordCube(); // all coords are set to 0
  CubieCube cubie;

  cubie.set_solved(); // all coords are set to 0

  // APPLYING STARTING MOVES TO CUBIECUBE AND COORDCUBE:
  for (size_t i = 0; i < 10; i++)
  {
    test->apply_move_phase_one(i);
    apply_move(&cubie.data, i);
  }
  std::cout << "\n" << std::endl;
  test->print();
  std::cout << "\n" << std::endl;
  cubie.print_all_coords();

  // RESOLVING RUBIKS: //
  Node *start = new Node(0, 0, test);
  vector<int> path;

  // PHASE 1:
  path = ida(start, phase_one_goal, phase_1_heuristic, g_plusone, create_baby_from_move_phase_one);
  print_path(path);
  std::cout << "\n" << std::endl;
  //  applying phase 1 path to the cubie to get the starting coords for phase 2:
  for (size_t i = 0; i < path.size(); i++)
    apply_move(&cubie.data, path[i]);
  // applying cubie coords to the cubecoord:
  test->corner_permutation_coord = cubie.corner_perm_coord();
  test->edge_permutation_coord = cubie.edge_perm_coord();
  test->UD_slice2_coord = cubie.UD2_coord();

  // PHASE 2:
  path = ida(start, phase_two_goal, phase_2_heuristic, g_plusone, create_baby_from_move_phase_two);
  print_path(path);
  for (size_t i = 0; i < path.size(); i++)
    apply_move(&cubie.data, path[i]);

  // SUPPOSED RESOLVED CUBE:
  std::cout << "\n" << std::endl;
  cubie.print_all_coords();
}

void  showing_what_is_wrong(void)
{
  CoordCube *test = new CoordCube(); // all coords are set to 0
  CubieCube cubie;

  cubie.set_solved(); // all coords are set to 0

  // APPLYING STARTING MOVES TO CUBIECUBE AND COORDCUBE:
  for (size_t i = 0; i < 10; i++)
  {
    test->apply_move_phase_one(i);
    apply_move(&cubie.data, i);
  }
  std::cout << "\nCOORDCUBE COORDS (phase two coords should be = to 0)" << std::endl;
  test->print();
  std::cout << "\nCUBIE CUBE COORDS (first 3 coords should be the same as COORDCUBE)" << std::endl;
  cubie.print_all_coords();
}

int		main(void)
{
  showing_what_is_wrong();
  return 0;
}