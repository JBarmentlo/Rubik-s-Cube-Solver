#ifndef DEFINE_HPP
#define DEFINE_HPP


#define FIRST_CORNER 			URF
#define LAST_CORNER 			DRB
#define FIRST_EDGE 				UR
#define LAST_EDGE 				BR

#define N_UD 					(unsigned int)495 // Max values for coordinates
#define N_CORNER_ORI 			(unsigned int)2187
#define N_EDGE_ORI 				(unsigned int)2048
#define N_CORNER_PERMUTATION 	(unsigned int)40320

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


#define N_THREADS 	9
#define N_MUTEX 	32
#define UNFILLED 	15
#define HSIZEONE	N_EDGE_ORI * N_CORNER_ORI * N_UD

typedef enum {
    URF, UFL, ULB, UBR, DFR, DLF, DBL, DRB
} corner_t;

inline corner_t operator++ (corner_t &d, int) {
	corner_t tmp = d;
    d = static_cast<corner_t>((static_cast<int>(d) + 1));
	return tmp;
}

inline corner_t operator-- (corner_t &d, int) {
	corner_t tmp = d;
    d = static_cast<corner_t>((static_cast<int>(d) - 1));
	return tmp;
}


typedef enum {
    UR, UF, UL, UB, DR, DF, DL, DB, FR, FL, BL, BR
} edge_t;

inline edge_t operator++ (edge_t &d, int) {
	edge_t tmp = d;
    d = static_cast<edge_t>((static_cast<int>(d) + 1));
	return tmp;
}

inline edge_t operator-- (edge_t &d, int) {
	edge_t tmp = d;
    d = static_cast<edge_t>((static_cast<int>(d) - 1));
	return tmp;
}
#define CORNER_ORI_HEURISTIC_NAME 	"../tables/heuristics/corner_orientation_heuristics"
#define EDGE_ORI_HEURISTIC_NAME 	"../tables/heuristics/edge_orientation_heuristics"
#define UD_SLICE1_HEURISTIC_NAME 	"../tables/heuristics/UD_slice1_heuristics"

#define CORNER_PERM_HEURISTIC_NAME 	"../tables/heuristics/corner_permutation_heuristics"
#define EDGE_PERM_HEURISTIC_NAME 	"../tables/heuristics/edge_permutation_heuristics"
#define UD_SLICE2_HEURISTIC_NAME 	"../tables/heuristics/UD_slice2_heuristics"


#define EDGE_PERMUTATION_2_NAME 	"../tables/moves/edge_perm_2_move"
#define CORNER_PERMUTATION_NAME 	"../tables/moves/corner_perm_2_move"
#define PHASE_ONE_HEURISTIC_NAME 	"../tables/heuristics/phase_1_h_table"

#define SPLIT_ONE_NAME				"../tables/heuristics/onehalf12"
#define SPLIT_TWO_NAME				"../tables/heuristics/twohalf12"

#define CORNER_ORI_NAME				"../tables/moves/corner_ori_move"
#define EDGE_ORI_NAME				"../tables/moves/edge_ori_move"
#define UD_SLICE_NAME				"../tables/moves/UD_slice_move"

#define UD_2_NAME	 				"../tables/moves/ud_2_move"
#define UD_2_THEO_NAME			    "../tables/moves/ud_2_big_move"
#endif

