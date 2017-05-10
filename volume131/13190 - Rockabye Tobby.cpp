#include <bits/stdc++.h>
using namespace std;

int main() {
	int testcase;
	int n, m;
	static const int MAXN = 4096;
	static char s[MAXN][32];
	static int A[MAXN];
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &n, &m);
		set< pair<int, int> > S;
		for (int i = 0; i < n; i++) {
			scanf("%s %d", s[i], &A[i]);
			S.insert(make_pair(A[i], i));
		}
		for (int i = 0; i < m; i++) {
			pair<int, int> t = *S.begin();
			S.erase(t);
			printf("%d %s\n", t.first, s[t.second]);
			S.insert(make_pair(t.first + A[t.second], t.second));
		}
	}
	return 0;
}
/*
1
2 5
Acetaminophen 20
Loratadine 30
*/

