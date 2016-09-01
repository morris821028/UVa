#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 10;
int dp[MAXN][1<<MAXN], from[MAXN][1<<MAXN];
int main() {
	int testcase, N;
    int type[20][20];
    scanf("%d", &testcase);
    while (testcase--) {
    	scanf("%d", &N);
    	
    	int sum = 0;
    	for (int i = N-1; i >= 0; i--) {
    		for (int j = 0; j < N; j++)
    			scanf("%d", &type[i][j]), sum += type[i][j];
    	}
    	    	
    	memset(dp, 0, sizeof(dp));
    	memset(from, 63, sizeof(from));
    	for (int i = 0; i < N; i++)
    		dp[0][1<<i] = type[0][i], from[0][1<<i] = i;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < (1<<N); j++) {
				for (int k = 0; k < N; k++) {
					if ((j>>k)&1)	continue;
					if (dp[i][j] + type[i+1][k] > dp[i+1][j|(1<<k)])
						dp[i+1][j|(1<<k)] = max(dp[i+1][j|(1<<k)], dp[i][j] + type[i+1][k]);
					if (dp[i][j] + type[i+1][k] == dp[i+1][j|(1<<k)])
						from[i+1][j|(1<<k)] = min(k, from[i+1][j|(1<<k)]);
				}
			}
		}
		
		int ret = dp[N-1][(1<<N)-1];
		int sol[MAXN];
		for (int i = N-1, q = (1<<N)-1; i >= 0; i--) {
			sol[i] = from[i][q];
			q ^= 1<<sol[i];
		}
		for (int i = N-1; i >= 0; i--) {
			printf("%d", sol[i]);
		}
		printf(" %d\n", sum - ret);
    }
	return 0;
}
/*
1
3 
10 17 1 
9 9 8 
12 19 11
*/
