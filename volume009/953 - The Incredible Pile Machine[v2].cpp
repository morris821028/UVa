#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 10;
int dp[MAXN][1<<MAXN], used[MAXN][1<<MAXN];
int main() {
	int testcase, N;
    int type[20][20];
    scanf("%d", &testcase);
    while (testcase--) {
    	scanf("%d", &N);
    	
    	int sum = 0;
    	for (int i = 0; i < N; i++) {
    		for (int j = 0; j < N; j++)
    			scanf("%d", &type[i][j]), sum += type[i][j];
    	}
    	    	
    	memset(dp, 0, sizeof(dp));
    	memset(used, 0, sizeof(used));
    	for (int i = 0; i < N; i++)
    		dp[0][1<<i] = type[0][i];
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < (1<<N); j++) {
				for (int k = 0; k < N; k++) {
					if ((j>>k)&1)	continue;
					dp[i+1][j|(1<<k)] = max(dp[i+1][j|(1<<k)], dp[i][j] + type[i+1][k]);
				}
			}
		}
		
		used[N-1][(1<<N) - 1] = 1;
		for (int i = N-2; i >= 0; i--) {
			for (int j = 0; j < (1<<N); j++) {
				for (int k = 0; k < N; k++) {
					if ((j>>k)&1)	continue;
					if (used[i+1][j|(1<<k)] && dp[i+1][j|(1<<k)] == dp[i][j] + type[i+1][k])
						used[i][j] = 1;
				}
			}
		}
		int ret = dp[N-1][(1<<N)-1];
		for (int i = 0, p, q = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if ((q>>j)&1)
					continue;
				if (used[i][q|(1<<j)]) {
					p = j, q |= 1<<j;
					break;
				}
			}
			printf("%d", p);
		}
		printf(" %d\n", sum - ret);
    }
	return 0;
}
