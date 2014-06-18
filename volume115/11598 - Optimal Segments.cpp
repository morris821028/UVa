#include <stdio.h>
#include <string.h>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;
int V[35], N, K;
int dp[31][16][30*26 + 5]; // [i-th][segment_count][min_value]
int ac_dp[31][16][30*26 + 5];
void solve() {
	int i, j, k, prev;
	int sum[35] =  {}, sumX[35] = {}, nextX[35] = {};
	for(i = 1; i <= N; i++) {
		sum[i] = sum[i-1] + V[i];
		sumX[i] = sumX[i-1] + (V[i] == 0);
	}
	for(i = N, prev = N+1; i >= 0; i--) {
		nextX[i] = prev;
		if(V[i] == 0)
			prev = i;
	}
	if(sumX[N] < K) {
		puts("not possible!");
		return ;
	} 
	set<int> R[31][16];
	dp[0][0][0] = 0, R[0][0].insert(0);
	for(i = 0; i < N; i++) {
		for(j = 0; j < K; j++) {
			for(set<int>::iterator it = R[i][j].begin();
				it != R[i][j].end(); it++) {
				for(k = nextX[i]; k <= N; k++) {
					int s = sum[k] - sum[i];
					int mn = min(*it, s), mx = max(dp[i][j][*it], s);
					if(i == 0)	mn = mx = s;
					if(R[k][j+1].find(mn) == R[k][j+1].end())
						R[k][j+1].insert(mn), dp[k][j+1][mn] = 0xfffffff, ac_dp[k][j+1][mn] = 0;
					dp[k][j+1][mn] = min(dp[k][j+1][mn], mx);
				}
			}
		}
	}
	int ret = 0xfffffff;
	for(set<int>::iterator it = R[N][K].begin();
		it != R[N][K].end(); it++)  {
		ret = min(ret, dp[N][K][*it] - *it);
	}
	if(ret >= 50) {
		puts("overflow");
		return;
	}
	printf("%lld ", 1LL<<ret);
	vector< pair<int, int> > P;
	for(set<int>::iterator it = R[N][K].begin();
		it != R[N][K].end(); it++)  {
		if(ret == dp[N][K][*it] - *it) {
			ac_dp[N][K][*it] = 1;
			P.push_back(make_pair(*it, dp[N][K][*it]));
		}
	}	
	for(i = N; i >= 0; i--) {
		for(j = 0; j < K; j++) {
			for(set<int>::iterator it = R[i][j].begin();
				it != R[i][j].end(); it++) {
				for(k = nextX[i]; k <= N; k++) {
					int s = sum[k] - sum[i];
					int mn = min(*it, s), mx = max(dp[i][j][*it], s);
					if(i == 0)	mn = mx = s;
					if(ac_dp[k][j+1][mn]) {
						int ok = 0;
						for(int p = 0; p < P.size(); p++) {
							if(*it >= P[p].first && dp[i][j][*it] <= P[p].second)
								ok = 1;
						}
						if(ok) {
							ac_dp[i][j][*it] = ok;
							break;
						}
					}
				}
			}
		}
	}
	int idx = 0, idx_mn = 0;
	for(int seg = 0; seg < K; seg++) {
		for(j = N; j >= idx; j--) {
			if(sumX[j] - sumX[idx] == 0)
				continue;
			int s = sum[j] - sum[idx];
			int mn = min(idx_mn, s), mx = max(dp[idx][seg][idx_mn], s);
			if(idx == 0)	mn = mx = s;
			if(ac_dp[j][seg+1][mn]) {
				putchar('(');
				for(k = idx+1; k <= j; k++) {
					if(V[k])
						printf("%d", V[k]);
					else
						printf("X"); 
					printf("%c", k == j ? ')' : ' ');
				}
				idx = j, idx_mn = mn;
				break;	
			}
		}
	}
	puts("");
}
int main() {
	int testcase, cases = 0;
	int i, j, k;
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d %d", &N, &K);
		for(i = 1; i <= N; i++) {
			char s[10];
			scanf("%s", s);
			if(s[0] == 'X')
				V[i] = 0;
			else
				sscanf(s, "%d", &V[i]);
		}
		printf("Case %d: ", ++cases);
		solve();
	}
	return 0;
}
/*
1000
20 6
X 3 7 X 2 4 6 3 X 6 9 4 X X 4 7 X X 5 6 
20 12
X X 2 X 7 2 X X X X 1 X X 9 X X X X 4 X 
*/
