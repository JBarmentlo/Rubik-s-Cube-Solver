#include "cubiecube.hpp"
#include "Node.hpp"
#include "ida.hpp"


using namespace std;


void check_identity()
{
	cubiecube_t* moves = get_moves();
	cubiecube_t one;
	cubiecube_t two;
	cubiecube_t three;

	for (int i = 0; i < 6; i++)
	{
		one = moves[i];
		two = moves[i + 6];
		three = moves[i + 12];
		std::cout << std::endl;

		apply_move(&one, &three);
		print_corners(&one);
		one = moves[i];
		std::cout << std::endl;


		apply_move(&three, &one);
		print_corners(&three);
		three = moves[i + 12];
		std::cout << std::endl;


		apply_move(&two, &two);
		print_corners(&two);
		two = moves[i + 6];
		std::cout << std::endl;
		std::cout << std::endl;
	}
}

int main()
{
	// cubiecube_t* moves = get_moves();
	// cubiecube_t R = create_cubie_with_corner_coord(1245);
	// // cubiecube_t R = moves[1];



	// // print_corners(&homecube);
	// print_corners(&R);
	// // apply_move(&R, &R);
	// // print_corners(&R);
	// // print_corners(&moves[1]);
	// std::cout << std::endl;
	// // print_edges(&homecube);
	// std::cout << std::endl;
	// // // c = create_cubie_with_corner_coord(49);
	
	// std::cout << corner_orientation_coordinate(&R) << std::endl;
	// std::cout << edge_orientation_coordinate(&R) << std::endl;
	// std::cout << corner_permutation_coordinate(&R) << std::endl;
	// std::cout << edge_permutation_coordinate(&R) << std::endl;
	// std::cout << UD_slice_coordinate(&R) << std::endl;

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