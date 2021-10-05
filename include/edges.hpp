#ifndef EDGES_HPP
#define EDGES_HPP


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

#endif