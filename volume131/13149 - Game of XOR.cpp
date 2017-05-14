#include <bits/stdc++.h>
using namespace std;
#define MAXG 16384
#define MAXS 131072
static char S[MAXS];
static int G;
const int64_t MOD = 342307123;

int64_t dp[MAXG][2][2][2] = {0};

void prepare() {
	dp[0][0][0][0] = 1, dp[0][0][1][0] = 1;
	dp[0][1][0][1] = 1,	dp[0][1][1][1] = 1;
	for (int i = 1; i < MAXG; i++) {
		for (int p = 0; p < 2; p++) {
			for (int q = 0; q < 2; q++) {
				dp[i][p][q][0] = dp[i-1][p][p^q][0] + dp[i-1][p^q][q][0];
				dp[i][p][q][1] = dp[i-1][p][p^q][1] + dp[i-1][p^q][q][1];
				if (dp[i][p][q][0] >= MOD)
					dp[i][p][q][0] -= MOD;
				if (dp[i][p][q][1] >= MOD)
					dp[i][p][q][1] -= MOD;
			}
		}
	}
}
pair<int64_t, int64_t> f(int pos, char cmd[], int G, int &Lval) {
	int64_t zo[2] = {};
	for (int i = 0; i < pos; i++) {
		zo[0] += dp[G-1][S[i]-'0'][S[i+1]-'0'][0];
		zo[1] += dp[G-1][S[i]-'0'][S[i+1]-'0'][1];
		if (zo[0] >= MOD)	zo[0] -= MOD;
		if (zo[1] >= MOD)	zo[1] -= MOD;
	}
	int L = S[pos]-'0', R = S[pos+1]-'0';
	for (int i = 1; i < G; i++) {
		if (cmd[i-1] == 'R') {
			zo[0] += dp[G-i-1][L][L^R][0];
			zo[1] += dp[G-i-1][L][L^R][1];
			if (zo[0] >= MOD)	zo[0] -= MOD;
			if (zo[1] >= MOD)	zo[1] -= MOD;
			L = L^R;
		} else {
			R = L^R;
		}
	}
	Lval = L;
	return pair<int64_t, int64_t>(zo[0], zo[1]);
}
int main() {
	prepare();
	static char sL[MAXS], sR[MAXS];
	int testcase, cases = 0;
	int Lpos, Rpos;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%s %d", S, &G);
		scanf("%d", &Lpos);
		if (G > 1)	scanf("%s", &sL);
		scanf("%d", &Rpos);
		if (G > 1)	scanf("%s", &sR);
		int zoL, zoR;
		pair<int64_t, int64_t> Lc = f(Lpos, sL, G, zoL), Rc = f(Rpos, sR, G, zoR);
		pair<int64_t, int64_t> ret(Rc.first-Lc.first, Rc.second-Lc.second);
		if (zoR == 0)
			ret.first++;
		else
			ret.second++;
		ret.first = (ret.first%MOD+MOD)%MOD;
		ret.second = (ret.second%MOD+MOD)%MOD;
		printf("Case %d: %lld %lld\n", ++cases, ret.first, ret.second);
	}
	return 0;
}
/*
3

10010  4
0  DRR
1  RDD

10010  1
0  
1  

01001  2
0  D
4  D

*/

