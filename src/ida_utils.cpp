#include "ida_utils.hpp"


bool            phase_one_goal(CoordCube* coordcube)
{
	if (coordcube->corner_orientation_coord == 0 and
	coordcube->edge_orientation_coord == 0 and
	coordcube->UD_slice_coord == 0)
	{
		return true;
	}
	return false;
}

bool            phase_two_goal(CoordCube* coordcube)
{
	if (coordcube->corner_permutation_coord == 0 and
	coordcube->edge_permutation_coord == 0 and
	coordcube->UD_slice2_coord == 0)
	{
		return true;
	}
	return false;
}


bool		corner_heuristic(CoordCube* coordcube)
{
	if (coordcube->corner_orientation_coord != 0)
		return (false);
	return (true);
}

void		set_corner_goal(CoordCube* coordcube)
{
	coordcube->corner_orientation_coord = 0;
}

vector<int>		ordered_path(stack<Node*> ida_path)
{
	Node*	tmp;
	vector <int> final_path(ida_path.size() - 1);
	int i;

	i = 0;
	while(ida_path.empty() == false)
	{
		tmp = ida_path.top();
		if (tmp->coordcube->origin_move != NO_MOVE_APPLIED)
			final_path[i] = tmp->coordcube->origin_move;
		ida_path.pop();
		i += 1;
	}
	std::reverse(final_path.begin(), final_path.end());
	return (final_path);
}

void	print_path(vector<int> path)
{
  for (size_t i = 0; i < path.size(); i++)
  {
    std::cout << "[" << path[i] << "]";
  }
}