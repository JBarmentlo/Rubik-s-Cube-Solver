#ifndef CUBICOOB
#define CUBICOOB

#include <cstring>

#include "cubiecube_utils.hpp"
#include "utils.hpp"




class CubieCube
{
private:
	/* data */
public:
	CubieCube(/* args */);
	~CubieCube();
	
	void 	multiply(cubiecube_t *move_cube); // Applies move to the cube
	void	multiply_corners(cubiecube_t *move_cube);
	void 	multiply_edges(cubiecube_t *move_cube);

	int 	corner_ori_coord();
	int 	corner_perm_coord();
	int 	edge_ori_coord();
	int 	edge_perm_coord();
	int 	UD_coord();
	int		UD2_coord();



	void 	set_corner_ori_coord(int coord);
	// void 	set_corner_perm_coord(int coord);
	void 	set_edge_ori_coord(int coord);
	// void 	set_edge_perm_coord(int coord);
	void 	set_UD_coord(int coord);

	void  	print_corners();
	void  	print_edges();
	void	set_solved();
	void	print_all_coords();


	cubiecube_t	data;
};

#endif
