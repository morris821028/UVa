#include <bits/stdc++.h>
using namespace std;

const int MAXN = 16777216;
const int MAXH = 100007;
const int PMUL = 107;
int main() {
	int testcase, n, nc;
	static char str[MAXN];
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &n, &nc);
		scanf("%s", str);
		
		int m = strlen(str);
		int ret = 0;
		uint32_t h = 0, hnc = 1;
		static vector<char*> hash[MAXH];
		for (int i = 0; i < MAXH; i++)
			hash[i].clear();
		for (int i = 0; i < n && i < m; i++)
			h = h*PMUL + str[i], hnc = hnc*PMUL;
		if (m >= n)
			hash[h%MAXH].push_back(str), ret++;
		for (int i = n; i < m; i++) {
			h = h*PMUL + str[i] - hnc*str[i-n];
//			printf("%u\n", h);
			uint32_t hh = h%MAXH;
			if (hash[hh].size() == 0) {
				hash[hh].push_back(str+i-n+1);
				ret++;
			} else {
				int has = 0;
				char *p = str+i-n+1;
				for (auto e: hash[hh]) {
					char *q = e;
					int same = 1;
					for (int j = 0; j < n && same; j++)
						same &= p[j] == q[j];
					if (same) {
						has = 1;
						break;
					}
				}
				if (!has) {
					hash[hh].push_back(str+i-n+1);
					ret++;
				}
			}
		}
		printf("%d\n", ret);
		if (testcase)
			puts("");
	}
	return 0;
}
/*
1
3 4
daababac
*/
