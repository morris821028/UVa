#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

typedef struct Node {
	int type, x;
	char s[32];
	struct Node *lson, *rson;
} Node;

Node nodes[1024];
int nodesize = 0;
char expr[1024], *eptr;
char peek() {
	while (isspace(*eptr))
		eptr++;
	return *eptr;
}
void fetch(char c) {
	assert(peek() == c);
	eptr++;
}
Node* newNode() {
	Node *p = &nodes[nodesize++];
	return p;
}
Node* parser() {
	char c = peek();
	Node *u = newNode();
	if (c == '(') {
		u->type = 1;
		fetch('(');
		u->x = peek(), fetch(u->x);
		u->lson = parser();
		u->rson = parser();
		fetch(')');
	} else if (isdigit(c)) {
		u->type = 2;
		sscanf(eptr, "%d", &(u->x));
		while (isdigit(*eptr))
			eptr++;
	} else {
		u->type = 3;
		sscanf(eptr, "%s", u->s);
		while (isdigit(*eptr) || isalpha(*eptr) || *eptr == '_')
			eptr++;
	}
	return u;
}

char var_name[256][256];
int var_val[256], var_cnt;
int compute(Node *u) {
	if (u->type == 1) {
		switch(u->x) {
			case '+':
				return compute(u->lson) + compute(u->rson);
			case '-':
				return compute(u->lson) - compute(u->rson);
			case '*':
				return compute(u->lson) * compute(u->rson);
			case '/':
				return compute(u->lson) / compute(u->rson);
		}
	}
	if (u->type == 2)
		return u->x;
	for (int i = 0; i < var_cnt; i++) {
		if (!strcmp(var_name[i], u->s))
			return var_val[i];
	}
	return 0;
}
int main() {
	fgets(expr, 1024, stdin);
	
	eptr = expr;
	nodesize = 0;
	Node *root = parser();
	
	char buf[1024], s[1024];
	var_cnt = 0;
	while (fgets(buf, 1024, stdin)) {
		int x;
		if (sscanf(buf, "%s %*s %d", var_name[var_cnt], &var_val[var_cnt]) == 2)
			var_cnt++;
	}
	
	printf("%d\n", compute(root));
	return 0;
}

