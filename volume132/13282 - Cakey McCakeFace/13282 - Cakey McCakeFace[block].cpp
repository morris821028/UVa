#include <bits/stdc++.h> 
using namespace std;
const int MAXN = 2048;
int A[MAXN], B[MAXN];
uint16_t C[1<<16][2];
int main() {
	int n, m;
	while (scanf("%d %d", &n, &m) == 2) {
		for (int i = 0; i < n; i++)
			scanf("%d", &A[i]);
		for (int i = 0; i < m; i++)
			scanf("%d", &B[i]);
		vector<uint16_t> bin[1<<16];
		for (int i = 0; i < m; i++) {
			int v = B[i];
			for (int j = 0; j < n && A[j] < v; j++) {
				int d = v-A[j];
				bin[d>>16].push_back(d&((1<<16)-1));
			}
		}
		
		for (int i = 0; i < (1<<16); i++)
			C[i][0] = C[i][1] = 0;
		int mx = 0, ret = 0;
		for (int i = 0, cases = 0; i < (1<<16); i++) {
			++cases;
			for (auto e : bin[i]) {
				uint16_t *c = C[e];
				if (c[0] != cases) c[0] = cases, c[1] = 0;
				c[1]++;
				if (c[1] >= mx) {
					int x = (i<<16)|e;
					if (c[1] > mx || x < ret)
						mx = c[1], ret = x;
				}
			}
		}
		printf("%d\n", ret);
	}
	return 0;
}
/*
5
5
0  10  12  20  30
1  5  17  27  50
*/
