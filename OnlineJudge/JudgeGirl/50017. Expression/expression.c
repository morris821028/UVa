#include "expression.h"
#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include <limits.h>
#include <string.h>

static int eflag = 0;
static char *eptr = NULL;
static int merge(int a, int b, int op) {
	if (eflag)	return 0;
	switch(op) {
		case '+': return a + b;
		case '-': return a - b;
		case '*': return a * b;
		case '/': if (b == 0) {eflag = 1; return 0;}
				return a / b;
	}
}
static int peek() {
	if (eflag)	return EOF;
	while (isspace(*eptr))
		eptr++;
	return eptr[0];
}
static void fetch(char c) { 
	if (eflag)	return ;
	if (peek() != c) {
		eflag = 1;
		return ;
	}
	eptr++; 
}
static int dfs() {
	if (eflag)	return 0;
	if (peek() == '-') {
		fetch('-');
		return - dfs();
	}
	if (isdigit(peek())) {
		int x = 0;
		while (isdigit(peek()))
			x = x * 10 + peek() - '0', eptr++;
		return x;
	}
	int rh1, rh2, op = -1;
	fetch('(');
	rh1 = dfs();
	op = peek(), eptr++;
	rh2 = dfs();
	fetch(')');
	return merge(rh1, rh2, op);
}
int expression(char *s) {
	eflag = 0, eptr = s;
	int ret = dfs();
	fetch('\0');
	return eflag ? INT_MIN : ret;
}
