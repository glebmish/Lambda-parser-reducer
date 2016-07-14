#pragma once

#include <string>
#include <iostream>
#include <list>
using namespace std;

#include "Node.h"
#include "Pool.h"

class Abs : public Node {
	int l;
	Node* r;

public:

	Abs(int ll, Node* rr): l(ll), r(rr) {}

	void* operator new (size_t n, Pool* pool);
	void operator delete (void* ptr, Pool* pool) {free(ptr);}

	void getexp(ostream& out, bool isapp, bool isleft);
	void gettree(ostream& out, bool isDebug = 0, int = 0, list<int> = list<int>());

	string saymyname();
	int getvalue();

	Node* reduce(Pool* pool);
	bool isredex();
	Node* substitute(Pool* pool, int, int, Node*);
	Node* changeprior(Pool* pool, int, map<int, int> = map<int,int>());

	Node* copy(Pool* pool);

	~Abs() {delete r;}
};