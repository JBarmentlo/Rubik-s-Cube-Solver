#ifndef MOVE_TABLES_H
#define MOVE_TABLES_H

#include "cubiecube_utils.hpp"

typedef int (*get_coord_function)(cubiecube_t*);
typedef void (*set_coord_function)(cubiecube_t*);


void make_raw_move_table(int (*get_coord)(cubiecube_t*),)

#endif