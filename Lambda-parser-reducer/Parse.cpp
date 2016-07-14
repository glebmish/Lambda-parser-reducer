#include "Parse.h"

Tree Parse::parse() {
	Pool* pool = new Pool();
	Node *x = parse_L(1, pool);
	if (t.getKind() != tokenizer::ENOF) {
		delete x;
		throw ParseError(t.getPos(), t.getChar(), "\\0");
	}
	return Tree(pool, x);
}

Node* Parse::parse_L(int k, Pool* pool) {
	Node* l = parse_T(k, pool);
	if (l == NULL) throw ParseError(t.getPos(), t.getChar());
	try {
		while (t.getKind() != tokenizer::ENOF) {
			Node* r = parse_T(k, pool);
			if (r == NULL) break;
			l = new(pool) App(l, r);
		}
	} catch (ParseError e) {
		delete l;
		throw e;
	}
	return l;
};
		

Node* Parse::parse_T(int k, Pool* pool) {
	if (t.getKind() == tokenizer::LAMBDA) {
		t.Next();
		string s = t.getString();
		t.Next();
		if (t.getKind() != tokenizer::POINT) throw ParseError(t.getPos(), t.getChar(), ".");
		t.Next();
		int tmp = m[s];
		m[s] = k;
		Node* n = parse_L(k + 1, pool);
		m[s] = tmp;

		return new(pool) Abs(k, n);
	} else if (t.getKind() == tokenizer::VAR) {
		string s = t.getString();
		t.Next();

		if (m.count(s) && m[s] != 0)
			return new(pool) Var(m[s]);
		else {
			m[s] = freect--;
			return new(pool) Var(m[s]);
		}
	} else if (t.getKind() == tokenizer::OBRACKET) {
		t.Next();
		Node* n = parse_L(k, pool);
		if (t.getKind() != tokenizer::CBRACKET) throw ParseError(t.getPos(), t.getChar(), ")");
		t.Next();

		return n;
	} else
		return NULL;
}