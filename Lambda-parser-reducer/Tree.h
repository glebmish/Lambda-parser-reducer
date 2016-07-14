#pragma once

#include "Node.h"
#include "Pool.h"

class Tree {
	Pool* pool;
	Node* tree;

public:

	Tree(Pool* p, Node* n): pool(p), tree(n) {}

	bool is_full_pool();
	void refresh_pool();
	void clean();
	void debug_inf();

	void getexp(ostream& out);
	void gettree(ostream& out);
	void reduce();
	bool isredex();
};