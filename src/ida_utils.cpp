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
