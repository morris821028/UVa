#include "expression.h"
#include <limits.h>
#include <string.h>
#include <ctype.h>

int eflag = 0;
char* trim(char *s) {
	while (isspace(*s))	s++;
	char *p = s;
	while (*p)	p++;
	p--;
	while (isspace(*p))
		*p = '\0', p--;
	return s;
}
int merge(int a, int b, int op) {
	if (eflag)	return 0;
	switch(op) {
		case 0: return a + b;
		case 1: return a - b;
		case 2: return a * b;
		case 3: if (b == 0) {eflag = 1; return 0;}
				return a / b;
	}
}
int dfs(char *s) {
	if (eflag)	return 0;
	s = trim(s);
	if (s[0] == '-')
		return - dfs(s+1);
	int n = strlen(s);
	int pp = 0;
	int priL, priH, posL, posH;
	priL = priH = posL = posH = -1;
	for (int i = 0; i < n; i++) {
		if (s[i] == '(') {
			pp++;
		} else if (s[i] == ')') {
			pp--;
		} else {
			if (pp == 0) {
				if (s[i] == '+' || s[i] == '-') {
					if (priL == -1)
						priL = s[i], posL = i;
				}
				if (s[i] == '*' || s[i] == '/') {
					if (priH == -1)
						priH = s[i], posH = i;
				}
			}
		}
	}
	if (priL == -1 && priH == -1) {
		if (s[0] == '(' && s[n-1] == ')') {
			s[n-1] = '\0';
			return dfs(s+1);
		} else {
			return s[0] - '0';
		}
	}
	if (priL != -1) {
		s[posL] = '\0';
		if (priL == '+')
			return merge(dfs(s), dfs(s + posL + 1), 0);
		else
			return merge(dfs(s), dfs(s + posL + 1), 1);
	} else {
		s[posH] = '\0';
		if (priH == '*')
			return merge(dfs(s), dfs(s + posH + 1), 2);
		else
			return merge(dfs(s), dfs(s + posH + 1), 3);
	}
	return 0;
}
int expression(char *s) {
	eflag = 0;
	int ret = dfs(s);
	return eflag ? INT_MIN : ret;
}
