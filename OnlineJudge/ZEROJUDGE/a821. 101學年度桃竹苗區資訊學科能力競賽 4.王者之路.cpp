#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, m;
	while (scanf("%d %d", &n, &m) == 2) {
		char s1[128], s2[128];
		map<string, set<string> > P;
		map<string, int> Q;
		for (int i = 0; i < m; i++) {
			scanf("%s %s", s1, s2);
			Q[s2] = 1;
			P[s1].insert(s2);
		}
		for (auto &x : P) {
			if (x.second.size() == n-1 && Q[x.first] == 0)
				printf("%s\n", x.first.c_str());
		}
	}
	return 0;
}

