#include "CubieCube.hpp"
#include "cubiecube_utils.hpp"
#include "utils.hpp"



CubieCube::CubieCube(/* args */)
{
}


CubieCube::~CubieCube()
{
}



void 	CubieCube::multiply(cubiecube_t *move_cube)
{
	apply_move(&this->data, move_cube);
}


void	CubieCube::multiply_corners(cubiecube_t *move_cube)
{
	apply_move_corners(&this->data, move_cube);
}


void 	CubieCube::multiply_edges(cubiecube_t *move_cube)
{
	apply_move_edges(&this->data, move_cube);
}


int 	CubieCube::corner_ori_coord()
{
	return (corner_orientation_coordinate(&this->data));
}


int 	CubieCube::corner_perm_coord()
{
	return (corner_permutation_coordinate(&this->data));
}


int 	CubieCube::edge_ori_coord()
{
	return (edge_orientation_coordinate(&this->data));
}


int 	CubieCube::edge_perm_coord()
{
	return (edge_permutation_coordinate(&this->data));
}


int 	CubieCube::UD_coord()
{
	return (UD_slice_coordinate(&this->data));
}


void  	CubieCube::print_corners()
{
	for (int i = 0; i < CORNER_NUM; i++)
	{
		std::cout << corner_position_to_string(this->data.corner_positions[i]) << "\t";
	}
	std::cout << std::endl;
	for (int i = 0; i < CORNER_NUM; i++)
	{
		std::cout << (int)this->data.corner_orientations[i] << "  \t";
	}
	std::cout << std::endl;
}


void  	CubieCube::print_edges()
{
	for (int i = 0; i < EDGE_NUM; i++)
	{
		std::cout << edge_position_to_string(this->data.edge_positions[i]) << "\t";
	}
	std::cout << std::endl;
	for (int i = 0; i < EDGE_NUM; i++)
	{
		std::cout << (int)this->data.edge_orientations[i] << "  \t";
	}
	std::cout << std::endl;
}


void	CubieCube::set_solved()
{
	memcpy(&this->data, &homecube, sizeof(this->data));
}
