#include <bits/stdc++.h>
using namespace std;

char A[1024][1024];
int main() {
	int R, C, Q;
	int lx, ly, rx, ry;
	set<int> row[1024];
	scanf("%d %d", &R, &C);
	scanf("%d", &Q);
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++)
			row[i].insert(j);
	}
	for (int i = 0; i < Q; i++) {
		scanf("%d %d %d %d", &lx, &ly, &rx, &ry);
		vector< pair<int, int> > ret;
		for (int p = lx; p <= rx; p++) {
			set<int>::iterator it = row[p].lower_bound(ly);
			for (; it != row[p].end() && *it <= ry; ) {
				ret.push_back({p, *it});
				row[p].erase(it++);
			}
		}
		printf("%d", ret.size());
		for (auto &e : ret)
			printf(" (%d, %d)", e.first, e.second);
		puts("");
	}
	return 0;
}
