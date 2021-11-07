#ifndef DEFINE_HPP
#define DEFINE_HPP

#include <map>
#include <iostream>
#include <string>

#define VERBOSE					0

static std::map<int, std::string> moves_strings = {
	{0, "U"}, {1, "R"}, {2, "F"}, {3, "D"}, {4, "L"}, {5, "B"},
	{6, "U2"}, {7, "R2"}, {8, "F2"}, {9, "D2"}, {10, "L2"}, {11, "B2"},
	{12, "U'"}, {13, "R'"}, {14, "F'"}, {15, "D'"}, {16, "L'"}, {17, "B'"}};


static std::map<std::string, int> moves_numbers = {
	{"U", 0}, {"R", 1}, {"F", 2}, {"D", 3}, {"L", 4}, {"B", 5},
	{"U2", 6}, {"R2", 7}, {"F2", 8}, {"D2", 9}, {"L2", 10}, {"B2", 11},
	{"U'", 12}, {"R'", 13}, {"F'", 14}, {"D'", 15}, {"L'", 16}, {"B'", 17}};



#define FIRST_CORNER 			URF
#define LAST_CORNER 			DRB
#define FIRST_EDGE 				UR
#define LAST_EDGE 				BR

#define N_UD_1 					(unsigned int)495 // Max values for coordinates
#define N_CORNER_ORI_1 			(unsigned int)2187
#define N_EDGE_ORI_1			(unsigned int)2048

#define N_CORNER_PERMUTATION_2 	(unsigned int)40320
#define N_UD_2	 				24
#define N_UD_2_THEO				11880
#define N_EDGE_PERMUTATION_2 	40320

#define N_MOVES					18
#define N_MOVES_PHASE_2			10
#define N_BASIC_MOVES			6

#define EDGE_NUM 				12
#define CORNER_NUM 				8

static bool is_allowed_quarter_turns[6] = {true, false, false, true, false}; // Some faces are only allowed 180 turns in phase two

//  SOLVER DEFINES
#define MAX_ITER				10000
#define SUCCESS					-1
#define NO_MOVE_APPLIED 		-1
#define MAX_INT					2147483647
#define THRESHOLD_INIT			0


#define N_THREADS 	9
#define N_MUTEX 	32
#define UNFILLED 	15
#define HSIZEONE	N_EDGE_ORI_1 * N_CORNER_ORI_1 * N_UD_1
#define HSIZETWO_1	N_EDGE_PERMUTATION_2 * N_UD_2
#define HSIZETWO_2	N_CORNER_PERMUTATION_2 * N_UD_2



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

#define CORNER_PERM_2_HEURISTIC_NAME 	"../tables/heuristics/corner_permutation_heuristics"
#define EDGE_PERM_2_HEURISTIC_NAME 	"../tables/heuristics/edge_permutation_heuristics"
#define UD_SLICE_2_HEURISTIC_NAME 	"../tables/heuristics/UD_slice2_heuristics"


#define EDGE_PERMUTATION_2_NAME 	"../tables/moves/edge_perm_2_move"
#define CORNER_PERMUTATION_NAME 	"../tables/moves/corner_perm_2_move"
#define PHASE_ONE_HEURISTIC_NAME 	"../tables/heuristics/phase_1_h_table"
#define PHASE_TWO_HEURISTIC_NAME_1 	"../tables/heuristics/phase_2_h_table_1"
#define PHASE_TWO_HEURISTIC_NAME_2 	"../tables/heuristics/phase_2_h_table_2"


#define SPLIT_ONE_NAME				"../tables/heuristics/onehalf12"
#define SPLIT_TWO_NAME				"../tables/heuristics/twohalf12"

#define CORNER_ORI_NAME				"../tables/moves/corner_ori_move"
#define EDGE_ORI_NAME				"../tables/moves/edge_ori_move"
#define UD_SLICE_NAME				"../tables/moves/UD_slice_move"

#define UD_2_NAME	 				"../tables/moves/ud_2_move"
#define UD_2_THEO_NAME			    "../tables/moves/ud_2_big_move"



#define USAGE						"Usage:\n./Roobik [options: --verbose <verbose> --visu] <shuffle_string>\nOr\n./Roobik [options: --verbose <verbose> --visu] <number_of_shuffles>\n\n1- <shuffle_string> : letters separated by a space that correspond to an accepted move\nExample: ./Roobik \"F U R2 D' L2\"\n\n2- <number_of_shuffles> : an integer that correspons to how many random shuffles you want to start your rubiks cube solver with\nExample: ./Roobik 3\n\nOPTIONS:\n--verbose <verbose> : set the level of verbosity, <verbose> is an integer between 0 and 2\n--visu: if added as an option, it will launch the visual with the programm\n"							

#endif

