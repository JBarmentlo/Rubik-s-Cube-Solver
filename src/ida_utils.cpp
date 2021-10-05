#include "ida_utils.hpp"

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
