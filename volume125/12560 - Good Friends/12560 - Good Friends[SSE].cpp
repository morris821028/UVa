#include <bits/stdc++.h>
using namespace std;
const int MAXN = 32;
const int MAXM = 10005;
int C[MAXN] = {};
__attribute__ ((aligned(16))) int S[MAXM];

typedef int v4si __attribute__ ((vector_size (16)));
void solve(int n, int m) {
	int sm = (m)/5;
	int MASK = (1<<n)-1;
	unordered_set<int> M, N;
	unordered_map<int, int> T;
	vector<int> ret;
	for (int i = 0; i < n; i++) {
		if (C[i] >= sm)
			M.insert(1<<i);
		else
			MASK ^= 1<<i; 
	}
	
	while (M.size()) {
		N.clear();
		T.clear();
		for (auto e : M) {
			int ce1 = MASK^e, extend = 0;
			while (ce1) {
				int low1 = ce1&(-ce1); ce1 ^= low1;
				int next = e | low1, valid = 1;
				int ce2 = e ^ low1;
				while (ce2) {
					int low2 = ce2&(-ce2); ce2 ^= low2;
					int sub_next = next ^ low2;
					if (!M.count(sub_next)) {
						valid = 0;
						break;
					}
				}
				if (valid) {
					int &test = T[next];
					if (test == 0) {
						int com = 0, i;
						static __attribute__ ((aligned(16))) v4si v4s;
						static __attribute__ ((aligned(16))) v4si v4m;
						memset(&v4m, 0, sizeof(v4m));
						for (i = 0; i+4 <= m; i += 4) {
							v4s = *(v4si *) (S + i);
							v4m -= (v4s & next) == next;
						}
						for (; i < m; i++)
							com += (S[i]&next) == next;
						com += v4m[0] + v4m[1] + v4m[2] + v4m[3];
						if (com >= sm) {
							N.insert(next);
							test = 1;
						} else {
							test = -1;
						}
					}
					if (test == 1)
						extend = 1;
				}
			}
			if (!extend)
				ret.push_back(e);
		}
		M.swap(N);
	}
	printf("%d\n", ret.size());
	sort(ret.begin(), ret.end(), greater<int>());
	for (auto e : ret) {
		for (int i = n-1; i >= 0; i--) {
			if ((e>>i)&1) {
				printf("%d", n-i);
				e ^= 1<<i;
				putchar(e ? ' ' : '\n');
			}
		}
	}
}
int main() {
	int testcase, cases = 0;
	int n, m;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &n, &m);
		memset(C, 0, sizeof(C));
		for (int i = 0; i < m; i++) {
			int s = 0, x, k;
			scanf("%d", &k);
			for (int j = 0; j < k; j++) {
				scanf("%d", &x);
				s |= 1<<(n-x);
				C[n-x]++;
			}
			S[i] = s;
		}
		printf("Case %d: ", ++cases);
		solve(n, m);
		puts("");
	}
	return 0;
}
 /*
 1
10  10
7  1  2  3  4  5  6  7
7  2  4  5  6  7  9  10
8  1  2  4  5  6  7  9  10
6  2  5  6  7  8  10
6  1  3  4  6  9  10
8  1  2  4  5  6  7  9  10
6  1  2  3  5  6  7
6  2  5  6  7  8  10
7  2  5  6  7  8  9  10
8  2  3  4  5  6  7  9  10
 */
