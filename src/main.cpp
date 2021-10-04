#include "cubiecube.hpp"
#include "Node.hpp"
#include "ida.hpp"

#include "cubiecube_utils.hpp"
#include "CubieCube.hpp"

#include "utils.hpp"
#include "tests.hpp"
#include "move_tables.hpp"

using namespace std;

int** read_raw_move_table(int coord_max, std::string filename)
{
	int*			table;
	table = (int*)malloc(N_MOVES * (coord_max + 1) * sizeof(int));
	int**			pretty_table;
	pretty_table = (int**)malloc((coord_max + 1) * sizeof(int*));

	std::ifstream in(filename, std::ios_base::binary);
	in.read((char*)table, N_MOVES * (coord_max + 1) * sizeof(int));

	for (int i = 0; i < coord_max + 1; i++)
	{
		pretty_table[i] = &table[i * N_MOVES];
	}
	return pretty_table;
}




int main()
{
	// cubiecube_t* moves = get_moves();
	// cubiecube_t eo = create_cubie_with_edge_orientation_coord(1245);
	// cubiecube_t co = create_cubie_with_corner_orientation_coord(1111);
	// cubiecube_t test;
	// CubieCube cube;
	// std::cout << std::endl;
	// std::cout << std::endl;
	// auto table = read_raw_move_table(N_CORNER_ORI, "../tables/corner_ori_move");
	// for (int i = 0; i < 18; i++) 
	// {
	// 	std::cout << table[1][i] << std::endl;
	// }


	int		goal;

	goal = 42;
	
	Node*	start = new Node(0, 1, 0, 'a');
	Node*	b = new Node(0, 3, 0, 'b');
	Node*	c = new Node(0, 4, 0, 'c');
	Node*	d = new Node(0, 4, 0, 'd');
	Node*	e = new Node(0, 3, 0, 'e');
	Node*	f = new Node(0, 7, 0, 'f');
	Node*	g = new Node(0, 6, 0, 'g');
	Node*	h = new Node(0, 6, 0, 'h');
	Node*	i = new Node(0, 7, 0, 'i');
	Node*	j = new Node(0, 5, 0, 'j');
	Node*	k = new Node(0, 5, 0, 'k');
	Node*	l = new Node(0, 5, 0, 'l');
	Node*	m = new Node(0, 7, 0, 'm');
	Node*	n = new Node(0, 6, 0, 'n');
	Node*	o = new Node(0, 8, 0, 'o');
	Node*	p = new Node(0, 11, 0, 'p');
	Node*	q = new Node(0, 13, 0, 'q');
	Node*	r = new Node(0, 14, 42, 'r');
	Node*	s = new Node(0, 15, 0, 's');

	start->bebes = {b, c};
	b->bebes = {d, e};
	c->bebes = {j, k};
	d->bebes = {h, i};
	e->bebes = {f, g};
	f->bebes = {};
	g->bebes = {};
	h->bebes = {p, q};
	i->bebes = {};
	j->bebes = {l, m};
	k->bebes = {n, o};
	l->bebes = {};
	m->bebes = {r, s};
	n->bebes = {};
	o->bebes = {};
	p->bebes = {};
	q->bebes = {};
	r->bebes = {};
	s->bebes = {};

	ida(start, goal);



}