#ifndef DEFINE_HPP
#define DEFINE_HPP


#define FIRST_CORNER 			URF
#define LAST_CORNER 			DRB
#define FIRST_EDGE 				UR
#define LAST_EDGE 				BR

#define N_UD 					495 // Max values for coordinates
#define N_CORNER_ORI 			2187
#define N_EDGE_ORI 				2048
#define N_UD_2	 				24
#define N_UD_2_THEO				11880
#define N_EDGE_PERMUTATION_2 	40320
#define N_CORNER_PERMUTATION 	40320


#define N_MOVES					18
#define N_BASIC_MOVES			6

#define EDGE_NUM 				12
#define CORNER_NUM 				8

//  IDA DEFINES
#define MAX_ITER	10000
#define SUCCESS		-1



#define CORNER_ORI_NAME	"../tables/corner_ori_move"
#define EDGE_ORI_NAME	"../tables/edge_ori_move"
#define UD_SLICE_NAME	"../tables/UD_slice_move"

#endif