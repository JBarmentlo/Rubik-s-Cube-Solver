bool corner_heuristic(CoordCube* coordcube)
{
	if (coordcube->corner_orientation_coord != 0)
		return (false);
	return (true);
}
