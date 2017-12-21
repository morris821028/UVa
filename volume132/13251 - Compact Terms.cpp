#include <bits/stdc++.h> 
using namespace std;

set<string> S;
void dfs(char s[], int l, int r) {
	S.insert(s+l);
	int pos = -1;
	for (int i = l; i <= r; i++) {
		if (!isalpha(s[i])) {
			pos = i;
			break;
		}
	}
	if (pos == -1)
		return ;
	pos++;
	for (int i = pos, t = 0; i <= r; i++) {
		if (s[i] == '(') {
			t++;
		} else if (s[i] == ')') {
			t--;
		}
		if (s[i] == ',' || i == r) {
			if (t == 0 || i == r) {
				s[i] = '\0';
				dfs(s, pos, i-1);
				pos = i+1;
			} 
		}
	}
}
int main() {
	static char s[131072];
	while (scanf("%s", s) == 1) {
		int n = strlen(s);
		S.clear();
		dfs(s, 0, n-1);
		printf("%d\n", S.size());
	}
	return 0;
}
/*
f(g(h(a,a),h(a,a)),h(a,X),g(h(a,a),h(a,a)))
h(a,b)
h(a,a)
h(A,a)
CCPL
f(a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a,a)
f(g(a,X,a),g(a,a,X))
f(g(a,X,a),g(a,X,a))
*/
