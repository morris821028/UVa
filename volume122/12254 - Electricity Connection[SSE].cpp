#pragma GCC target("avx")
#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#include <x86intrin.h>
using namespace std;

char g[8][16];

static const int dx[] = {0, 0, 1, -1};
static const int dy[] = {1, -1, 0, 0};

static int32_t w[64] __attribute__ ((aligned(16)));
static int32_t dp[1<<8][64] __attribute__ ((aligned(16)));
const int INF = 0x3f3f3f3f;
void relax(int s) {
	static int8_t Q[1024];
	uint64_t inq = 0;
	int Qn = 0;
	for (int i = 0; i < 64; i++) {
		if (dp[s][i] != INF)
			Q[Qn++] = i, inq |= 1ULL<<i;
	}
	for (int i = 0; i < Qn; i++) {
		int u = Q[i];
		int x = u>>3, y = u&7;
		inq ^= 1ULL<<u;
		for (int k = 0; k < 4; k++) {
			int tx = x+dx[k], ty = y+dy[k];
			if (tx < 0 || ty < 0 || tx >= 8 || ty >= 8)
				continue;
			int v = tx<<3|ty;
			if (dp[s][v] > dp[s][u]+1+w[v]) {
				dp[s][v] = dp[s][u]+1+w[v];
				if (((inq>>v)&1) == 0) {
					inq |= 1ULL<<v;
					Q[Qn++] = v;
				}
			}
		}
	}
}
int main() {
	int testcase, cases = 0;
	int pl, pw;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &pl, &pw);
		for (int i = 0; i < 8; i++)
			scanf("%s", &g[i]);

		int n = 0, root = 0;
		int A[8];
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				int u = i<<3|j;
				if (g[i][j] == 'H')
					A[n++] = u, w[u] = 0;
				else if (g[i][j] == 'G')
					w[u] = 0, root = u;
				else if (g[i][j] == 'W')
					w[u] = pw;
				else if (g[i][j] == '.')
					w[u] = pl;
			}
		}

		memset(dp, 0x3f, sizeof(dp));

		for (int i = 0; i < n; i++)
			dp[1<<i][A[i]] = 0;
			
		for (int i = 1, h; i < (1<<n); i++) {
			if ((i&(-i)) == i)
				h = i-1;
			for (int k = (i-1)&i; k > h; k = (k-1)&i) {
				for (int j = 0; j+4 <= 64; j += 4) {
					__m128i mv = _mm_load_si128((__m128i*) (dp[i]+j));
					__m128i a = _mm_load_si128((__m128i*) (dp[k]+j));
					__m128i b = _mm_load_si128((__m128i*) (dp[i^k]+j));
					__m128i tm = _mm_add_epi32(a, b);
					__m128i c = _mm_load_si128((__m128i*) (w+j));
					__m128i tn = _mm_sub_epi32(tm, c);
					__m128i mn = _mm_min_epi32(mv, tn);
					_mm_store_si128((__m128i*) (dp[i]+j), mn);
				}
//					dp[i][j] = min(dp[i][j], dp[k][j]+dp[i^k][j]-w[j]);
			}

			relax(i);
		}
		
		int ret = dp[(1<<n)-1][root];
		printf("Case %d: %d\n", ++cases, ret);
	}
	return 0;
}
/*
2
0 10
H.W.WH..
..W.W...
..WGW...
........
........
........
........
........
0 0
H.W.WH..
..W.W...
..WGW...
........
........
........
........
........
*/
