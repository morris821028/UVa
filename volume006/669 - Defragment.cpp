#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10005;
int place[MAXN], target[MAXN];

struct cmp {
	bool operator() (const int x, const int y) const {
		return target[x] > target[y];
	}
};

int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		int n, m;
		scanf("%d %d", &n, &m);
		memset(place, 0, sizeof(place));
		memset(target, 0, sizeof(target));
		int tot = 1;
		for (int i = 1; i <= m; i++) {
			int x, pos;
			scanf("%d", &x);
			for (int j = 0; j < x; j++) {
				scanf("%d", &pos);
				place[pos] = tot;
				target[tot] = pos;
				tot++;
			}
		}

		set<int, cmp> Q;
		for (int i = 1; i <= n; i++) {
			if (place[i] == 0) {
				Q.insert(i);
			}
		}
		
		int opt = 0;
		int unplace = 1;
		while (Q.size() && unplace < tot) {
			int free = *Q.begin(); Q.erase(Q.begin());
			if (target[free]) {
				printf("%d %d\n", target[free], free);
				opt = 1;
				place[target[free]] = 0, place[free] = free;
				Q.insert(target[free]);
			} else {
				while (unplace < tot && place[unplace] == unplace)
					unplace++;
				if (unplace < tot) {
					printf("%d %d\n", unplace, free);
					opt = 1;
					place[free] = place[unplace];
					target[place[unplace]] = free;
					place[unplace] = 0;
					Q.insert(unplace);
				}
			}
		}

		if (!opt)
			puts("No optimization needed");

		if (testcase)
			puts("");
	}
	return 0;
}
/*
2
20 3
4 2 3 11 12
1 7
3 18 5 10

30 4
2 1 2
3 3 4 5
2 6 7
8 8 9 10 11 12 13 14 15
*/
