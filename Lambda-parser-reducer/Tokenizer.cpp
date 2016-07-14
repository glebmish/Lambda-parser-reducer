#include "Tokenizer.h"

tokenizer::kind tokenizer::getKind() {
	switch (s[pos]) {
		case '\\': return LAMBDA;
		case '(': return OBRACKET;
		case ')': return CBRACKET;
		case '.': return POINT;
		case '\0': return ENOF;
		default: 
			if (s[pos] >= 'a' && s[pos] <= 'z') return VAR;
			else return UNDEF;
	}
}

int tokenizer::getPos() {
	return pos;
}

string tokenizer::getString() {
	string str;
	int tmp = pos;
	while (s[tmp] >= 'a' && s[tmp] <= 'z')
			str += s[tmp++];
	return str;
}

char tokenizer::getChar() {
	return s[pos];
}

void tokenizer::Next() {
	if (getKind() == ENOF) return;
	kind k = getKind();
	if (k == VAR) {
		while (s[pos] >= 'a' && s[pos] <= 'z')
			++pos;
	} 
	else ++pos;
	while(s[pos] == ' ')
		++pos;
}