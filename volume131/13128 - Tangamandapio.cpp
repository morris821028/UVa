#include <bits/stdc++.h>
using namespace std;
const long long MOD = 1e9+9;
const int MAXS = 1024;
const int MAXK = 1024;

long long f[20] = {1};
char S[1024];
long long C[MAXS][MAXS] = {};
int Cflag[MAXS][MAXS] = {};

int sp_C(int a, int b) {	// C(a, b)
	if (Cflag[a][b] > MAXK)
		return MAXK;
	return C[a][b];
}

int main() {
	for (int i = 1; i < 20; i++)
		f[i] = f[i-1]*i;
	C[0][0] = 1;
	for (int i = 1; i < MAXS; i++) {
		C[i][0] = 1;
		for (int j = 1; j <= i; j++) {
			C[i][j] = C[i-1][j-1] + C[i-1][j];
			if (C[i][j] > MAXK)
				Cflag[i][j] = 1;
			else
				Cflag[i][j] = Cflag[i-1][j-1] | Cflag[i-1][j];
			if (C[i][j] >= MOD)
				C[i][j] -= MOD;
		}
	}
	static int dp[MAXS][MAXK] = {};
	while (scanf("%s", S) == 1) {
		int K;
		scanf("%d", &K);
		int Cnt[26] = {}, slen = strlen(S);
		for (int i = 0; S[i]; i++)
			Cnt[S[i]-'a']++;
		int sum = 0;
		for (int i = 0; i <= slen; i++)
			memset(dp[i], 0, sizeof(dp[0][0])*(slen+1));
		dp[0][1] = 1;
		
		vector<int> fac;
		for (int i = 1; i <= K; i++) {
			if (K%i == 0)
				fac.push_back(i);
		}
		
		for (int it = 0; it < 26; it++) {
			if (Cnt[it] == 0)
				continue;
			int n = Cnt[it];
			for (int i = sum; i >= 0; i--) {
				for (auto j : fac) {
					if (dp[i][j] == 0)
						continue;
					long long val = dp[i][j];
					for (int k = 1; k <= n; k++) {
						int tmp = sp_C(i+k, k);
						int way = j * tmp;
						if (way > K)
							break;
						if (K % way)
							continue;
						dp[i+k][way] += val * C[n][k] % MOD;
						if (dp[i+k][way] >= MOD)
							dp[i+k][way] -= MOD;
					}
				}
			}
			sum += Cnt[it];
		}
		
		int ret = 0;
		for (int i = 1; i <= slen; i++) {
			if (dp[i][K]) {
				ret += dp[i][K];
				if (ret >= MOD)
					ret -= MOD;
			}
		}
		printf("%d\n", ret);
	}
	return 0;
}
/*
aaab
3
abcc
2
bdmzkmvqxggg
1
*/
