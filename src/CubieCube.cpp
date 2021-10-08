#include "CubieCube.hpp"




CubieCube::CubieCube(/* args */)
{
}


CubieCube::~CubieCube()
{
}

unsigned int 	CubieCube::flat_coord()
{
	return (this->corner_ori_coord() * N_EDGE_ORI * N_UD + this->edge_ori_coord() * N_UD + this->UD_coord());
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


void 	CubieCube::set_corner_ori_coord(int coord)
{
	set_corner_orientation_coord(coord, &this->data);
}


void 	CubieCube::set_edge_ori_coord(int coord)
{
	set_edge_orientation_coord(coord, &this->data);
};


void 	CubieCube::set_UD_coord(int coord)
{
	set_UD_slice_coord(coord, &this->data);
}

void CubieCube::print()
{
    std::cout << "corner_orientation coord:   " << this->corner_ori_coord() << "\n";
    std::cout << "edge_orientation coord:     " << this->edge_ori_coord() << "\n";
    std::cout << "UD slice1 coord:            " << this->UD_coord() << "\n";
    // std::cout << "\ncorner_permutation coord:   " << this->corner_perm_coord() << "\n";
    // std::cout << "edge_permutation coord:     " << this->edge_perm_coord() << "\n";
    // // std::cout << "UD slice2 coord: [" << this->UD_slice2_coord() << "]\n";
	std::cout << "flat                        " <<  this->corner_ori_coord() * N_EDGE_ORI * N_UD + this->edge_ori_coord() * N_UD + this->UD_coord() << std::endl;
}