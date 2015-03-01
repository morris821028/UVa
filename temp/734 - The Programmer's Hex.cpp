#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <map>
#include <vector>
#include <set>
#include <iostream>
using namespace std;
// similar 12639 - Hexagonal Puzzle
struct Hex {
	int v[6], rotate;
	vector<int> m[10];
	int read(char s[]) {
		for (int i = 0; i < 6; i++)
			v[i] = s[i] - '0';
		return 1;
	}
	void normal() {
		int t[6], mnexp = 0;
		for (int i = 0; i < 6; i++)
			t[i] = v[i];
		for (int i = 1; i < 6; i++)
			if (t[i] < t[mnexp])	
				mnexp = i;
		for (int i = 0; i < 6; i++)
			v[i] = t[(mnexp + i)%6];
		for (int i = 0; i < 10; i++)
			m[i].clear();
		set<string> S;
		for (int i = 0; i < 6; i++) {
			string s = "";
			for (int j = 0; j < 6; j++)
				s += (v[(i+j)%6] + '0');
			if (S.count(s))
				continue;
			m[v[i]].push_back(i);
			S.insert(s);
		}
	}
	int next() {
		return v[(rotate+1)%6];
	}
	int prev() {
		return v[(rotate+5)%6];
	}
	void println() {
		for (int i = 0; i < 6; i++)
			printf("%d", v[(rotate+i)%6]);
		puts("");
	}
};
int used[7], path[7];
Hex h[7];
int dfs(int idx) {
	if (idx == 7) {
		puts("PEG   HEX   POSITION");
		puts("---   ---   --------");
		int topw[7] = {0, 3, 2, 1, 0, 5, 4};
		for (int i = 0; i < idx; i++) {
			printf(" %d     %c     ", i, path[i] + 'A');
			for (int j = 0; j < 6; j++) {
				printf("%d", h[path[i]].v[(h[path[i]].rotate+j+topw[i])%6]);
			}
			puts("");
		}
		return 1;
	}
//	printf("%d\n", idx);

//	puts("--");
//	getchar();
	if (idx == 0) { // center
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
					int x = h[path[0]].v[idx - 1];
					for (int j = 0; j < h[i].m[x].size(); j++) {
						path[idx] = i, h[i].rotate = h[i].m[x][j];
						if (dfs(idx + 1))	return 1;
					}
					used[i] = 0;
				}
			}
		} else if (idx < 6) {
			for (int i = 0; i < 7; i++) {
				if (used[i] == 0) {
					used[i] = 1;
					int x = h[path[0]].v[idx - 1];
					for (int j = 0; j < h[i].m[x].size(); j++) {
						path[idx] = i, h[i].rotate = h[i].m[x][j];
						if (h[path[idx-1]].prev() == h[i].next())
							if (dfs(idx + 1))	return 1;
					}
					used[i] = 0;
				}
			}
		} else {
			for (int i = 0; i < 7; i++) {
				if (used[i] == 0) {
					used[i] = 1;	
					int x = h[path[0]].v[idx - 1];
					for (int j = 0; j < h[i].m[x].size(); j++) {
						path[idx] = i, h[i].rotate = h[i].m[x][j];
						if (h[path[idx-1]].prev() == h[i].next() && h[path[1]].next() == h[i].prev())
							if (dfs(idx + 1))	return 1;
					}
					used[i] = 0;
				}
			}
		}
	}
	return 0;
}
int main() {
	char s[1024];
	while (true) {
		for (int i = 0; i < 7; i++) {
			if (scanf("%s", s) != 1)
				return 0;
			h[i].read(s);
			h[i].normal();
		}
		scanf("%*s");
		memset(used, 0, sizeof(used));
		int ret = dfs(0);
		if (!ret)
			puts("No solution possible");
		puts("************************************");
	}
	return 0;
}
/*
665403
444444
666666
123456
123456
040404
289766
*
123456
111111
222222
333333
444444
555555
666666
*
*/

