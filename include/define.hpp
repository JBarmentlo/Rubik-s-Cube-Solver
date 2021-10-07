#ifndef DEFINE_HPP
#define DEFINE_HPP

#include "corners.hpp"
#include "edges.hpp"
#include "moves.hpp"

#define FIRST_CORNER 			URF
#define LAST_CORNER 			DRB
#define FIRST_EDGE 				UR
#define LAST_EDGE 				BR

#define N_UD 					495 // Max values for coordinates
#define N_CORNER_ORI 			2187
#define N_EDGE_ORI 				2048
#define N_CORNER_PERMUTATION 	40320


#define N_UD_2	 				24
#define N_UD_2_THEO				11880
#define N_EDGE_PERMUTATION_2 	40320



#define N_MOVES					18
#define N_MOVES_PHASE_2			10
#define N_BASIC_MOVES			6

#define EDGE_NUM 				12
#define CORNER_NUM 				8

static bool is_allowed_quarter_turns[6] = {true, false, false, true, false}; // Some faces are only allowed 180 turns in phase two

//  IDA DEFINES
#define MAX_ITER				10000
#define SUCCESS					-1
#define NO_MOVE_APPLIED 		-1



#define CORNER_ORI_NAME			"../tables/moves/corner_ori_move"
#define EDGE_ORI_NAME			"../tables/moves/edge_ori_move"
#define UD_SLICE_NAME			"../tables/moves/UD_slice_move"

#define UD_2_NAME	 				"../tables/moves/ud_2_move"
#define UD_2_THEO_NAME			    "../tables/moves/ud_2_big_move"
#define EDGE_PERMUTATION_2_NAME 	"../tables/moves/edge_perm_2_move"
#define CORNER_PERMUTATION_NAME 	"../tables/moves/corner_perm_2_move"

#define CORNER_ORI_HEURISTIC_NAME 	"../tables/heuristics/corner_orientation_heuristics"
#define EDGE_ORI_HEURISTIC_NAME 	"../tables/heuristics/edge_orientation_heuristics"
#define UD_SLICE1_HEURISTIC_NAME 	"../tables/heuristics/UD_slice1_heuristics"

#define CORNER_PERM_HEURISTIC_NAME 	"../tables/heuristics/corner_permutation_heuristics"
#define EDGE_PERM_HEURISTIC_NAME 	"../tables/heuristics/edge_permutation_heuristics"
#define UD_SLICE2_HEURISTIC_NAME 	"../tables/heuristics/UD_slice2_heuristics"


#endif