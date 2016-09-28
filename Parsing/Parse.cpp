#include "Parse.h"

Tree Parse::parse() {
    Pool* pool = new Pool();
    Node *x = parse_L(1, pool);
    if (t.get_kind() != Tokenizer::ENOF) {
        delete x;
        throw ParseError(t.get_pos(), t.get_char(), "\\0");
    }
    return Tree(pool, x);
}

Node* Parse::parse_L(int k, Pool* pool) {
    Node* l = parse_T(k, pool);
    if (l == NULL) throw ParseError(t.get_pos(), t.get_char());
    try {
        while (t.get_kind() != Tokenizer::ENOF) {
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
    if (t.get_kind() == Tokenizer::LAMBDA) {
        t.next();
        string s = t.get_variable();
        t.next();
        if (t.get_kind() != Tokenizer::POINT) throw ParseError(t.get_pos(), t.get_char(), ".");
        t.next();
        int tmp = m[s];
        m[s] = k;
        Node* n = parse_L(k + 1, pool);
        m[s] = tmp;

        return new(pool) Abs(k, n);
    } else if (t.get_kind() == Tokenizer::VAR) {
        string s = t.get_variable();
        t.next();

        if (m.count(s) && m[s] != 0)
            return new(pool) Var(m[s]);
        else {
            m[s] = freect--;
            return new(pool) Var(m[s]);
        }
    } else if (t.get_kind() == Tokenizer::OBRACKET) {
        t.next();
        Node* n = parse_L(k, pool);
        if (t.get_kind() != Tokenizer::CBRACKET) throw ParseError(t.get_pos(), t.get_char(), ")");
        t.next();

        return n;
    } else
        return NULL;
}
