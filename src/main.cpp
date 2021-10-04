#include "cubiecube.hpp"
#include "Node.hpp"
#include "ida.hpp"

#include "cubiecube_utils.hpp"
#include "CubieCube.hpp"
#include "CoordCube.hpp"


#include "utils.hpp"
#include "tests.hpp"
#include "move_tables.hpp"

using namespace std;


int main()
{
	cubiecube_t* moves = get_moves();

	cubiecube_t eo = create_cubie_with_edge_orientation_coord(1245);
	cubiecube_t co = create_cubie_with_corner_orientation_coord(1111);


	// make_raw_move_table(corner_orientation_coordinate, set_corner_orientation_coord, N_CORNER_ORI, "../tables/corner_ori_move");
    // make_raw_move_table(UD_slice_coordinate, set_UD_slice_coord, N_UD, UD_SLICE_NAME);
    // make_raw_move_table(edge_orientation_coordinate, set_edge_orientation_coord, N_EDGE_ORI, EDGE_ORI_NAME);

	int move;
	CubieCube	cmp;
	coord_cube_t mommy_cube;
	coord_cube_t bb_cube;

	set_solved(&mommy_cube);

	move = 0;
	while (move < N_MOVES)
	{
		cmp.set_solved();
		cmp.multiply(&get_moves()[move]);

		std::cout << "*******\nCUBICUBE:\n";
		std::cout << cmp.corner_ori_coord() << std::endl;
		std::cout << cmp.edge_ori_coord() << std::endl;
		std::cout << cmp.UD_coord() << "\n\n\n";

		bb_cube = create_baby_from_move(mommy_cube, move);

		std::cout << "COORDCUBE:\n";
		std::cout << bb_cube.corner_orientation_coord << std::endl;
		std::cout << bb_cube.edge_orientation_coord << std::endl;
		std::cout << bb_cube.UD_slice_coord << "\n\n\n";

		move += 1;
	}	


	// int		goal;

	// goal = 42;
	
	// Node*	start = new Node(0, 1, 0, 'a');
	// Node*	b = new Node(0, 3, 0, 'b');
	// Node*	c = new Node(0, 4, 0, 'c');
	// Node*	d = new Node(0, 4, 0, 'd');
	// Node*	e = new Node(0, 3, 0, 'e');
	// Node*	f = new Node(0, 7, 0, 'f');
	// Node*	g = new Node(0, 6, 0, 'g');
	// Node*	h = new Node(0, 6, 0, 'h');
	// Node*	i = new Node(0, 7, 0, 'i');
	// Node*	j = new Node(0, 5, 0, 'j');
	// Node*	k = new Node(0, 5, 0, 'k');
	// Node*	l = new Node(0, 5, 0, 'l');
	// Node*	m = new Node(0, 7, 0, 'm');
	// Node*	n = new Node(0, 6, 0, 'n');
	// Node*	o = new Node(0, 8, 0, 'o');
	// Node*	p = new Node(0, 11, 0, 'p');
	// Node*	q = new Node(0, 13, 0, 'q');
	// Node*	r = new Node(0, 14, 42, 'r');
	// Node*	s = new Node(0, 15, 0, 's');

	// start->bebes = {b, c};
	// b->bebes = {d, e};
	// c->bebes = {j, k};
	// d->bebes = {h, i};
	// e->bebes = {f, g};
	// f->bebes = {};
	// g->bebes = {};
	// h->bebes = {p, q};
	// i->bebes = {};
	// j->bebes = {l, m};
	// k->bebes = {n, o};
	// l->bebes = {};
	// m->bebes = {r, s};
	// n->bebes = {};
	// o->bebes = {};
	// p->bebes = {};
	// q->bebes = {};
	// r->bebes = {};
	// s->bebes = {};

	// ida(start, goal);

}