#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <map>
using namespace std;
struct Hex {
	int v[6], m[7], rotate;
	int read() {
		for (int i = 0; i < 6; i++) {
			if (scanf("%d", &v[i]) == 1);
			else
				return 0;
		}
		return 1;
	}
	void normal() {
		int t[6], mnexp = 0;
		for (int i = 0; i < 6; i++)
			t[i] = v[i];
		for (int i = 1; i < 6; i++)
			if (t[i] == 1)	mnexp = i;
		for (int i = 0; i < 6; i++)
			v[i] = t[(mnexp + i)%6];
		for (int i = 0; i < 6; i++)
			m[v[i]] = i;
	}
	int getPos(int x) {
		return m[x];
	} 
	int next() {
		return v[(rotate+1)%6];
	}
	int prev() {
		return v[(rotate+5)%6];
	}
	void println() {
		for (int i = 0; i < 6; i++)
			printf("%d ", v[(rotate+i)%6]);
		puts("");
	}
};
int used[7], path[7];
Hex h[7];
int dfs(int idx) {
	if (idx == 7)
		return 1;
//	printf("%d\n", idx);
//	for (int i = 0; i < idx; i++) {
//		printf("%d : ", h[path[i]].rotate);
//		h[path[i]].println();
//	}
//	puts("--");
//	getchar();
	if (idx == 0) {
		for (int i = 0; i < 7; i++) {
			if (used[i] == 0) {
				used[i] = 1;
				path[idx] = i, h[i].rotate = 0;
				if (dfs(idx + 1))	return 1;
				used[i] = 0;
			}
		}
	} else {
		if (idx == 1) {
			for (int i = 0; i < 7; i++) {
				if (used[i] == 0) {
					used[i] = 1;
					path[idx] = i, h[i].rotate = h[i].getPos(h[path[0]].v[idx - 1]);
					if (dfs(idx + 1))	return 1;
					used[i] = 0;
				}
			}
		} else if (idx < 6) {
			for (int i = 0; i < 7; i++) {
				if (used[i] == 0) {
					used[i] = 1;
					path[idx] = i, h[i].rotate = h[i].getPos(h[path[0]].v[idx - 1]);
					if (h[path[idx-1]].prev() == h[i].next())
						if (dfs(idx + 1))	return 1;
					used[i] = 0;
				}
			}
		} else {
			for (int i = 0; i < 7; i++) {
				if (used[i] == 0) {
					used[i] = 1;
					path[idx] = i, h[i].rotate = h[i].getPos(h[path[0]].v[idx - 1]);
					if (h[path[idx-1]].prev() == h[i].next() && h[path[1]].next() == h[i].prev())
						if (dfs(idx + 1))	return 1;
					used[i] = 0;
				}
			}
		}
	}
	return 0;
}
int main() {
	while (true) {
		for (int i = 0; i < 7; i++) {
			if (!h[i].read())
				return 0;
			h[i].normal();
		}
		memset(used, 0, sizeof(used));
		int ret = dfs(0);
		puts(ret ? "YES" : "NO");
	}
	return 0;
}
/*
1 2 3 4 5 6
1 3 6 5 2 4
1 4 2 5 6 3
1 5 2 3 6 4
1 6 2 4 3 5
1 6 2 4 5 3
1 6 5 3 2 4

1 2 3 4 5 6
1 2 3 4 5 6
1 2 3 4 5 6
1 2 3 4 5 6
1 2 3 4 5 6
1 2 3 4 5 6
1 2 3 4 5 6
*/
