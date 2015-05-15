#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

const int MOD = 1000000007;
const int MAXN = 20;

int dp[2][1<<MAXN][MAXN], used[2][1<<MAXN][MAXN], ucases = 0;
int g[MAXN+20][MAXN+20];
int vaild(int i, int a, int b) { // a contract b
	if (i == 0)	return 1;
	return g[a+1][b+1];
}
int main() {
	for (int i = 1; i <= MAXN; i++) {
		for (int j = 1; j <= MAXN; j++)
			g[i][j] = __gcd(i, j) == 1;
	}
    int testcase, n;
    int A[MAXN];
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d", &n);
        
        int cant = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d", &A[i]);
            if (A[i])
            	cant |= 1<<(A[i]-1);
        }
        
        int flag = 0;
        int mask = (1<<n)-1;
        int ret = 0;
//        memset(dp, 0, sizeof(dp));
        ucases++;
		used[flag][0][0] = ucases;
        dp[flag][0][0] = 1;
        for (int i = 0; i < n; i++) {
            int p = flag, q = !flag;
            flag = 1 - flag;
            ucases++;
//            for (int j = mask; j >= 0; j--)
//            	for (int k = 0; k < n; k++)
//            		dp[q][j][k] = 0;
            for (int j = (1<<n)-1; j >= 0; j--) {
            	for (int k = 0; k < n; k++) {
            		if (used[p][j][k] != ucases-1)
            			continue;
            		int ways = dp[p][j][k];
            		if (ways == 0)
            			continue;
            		if (A[i] == 0) {
            			for (int p = 0; p < n; p++) {
            				if ((j>>p)&1)
            					continue;
            				if (!vaild(i, k, p))
            					continue;
            				if (used[q][j|(1<<p)][p] != ucases)
            					used[q][j|(1<<p)][p] = ucases, dp[q][j|(1<<p)][p] = 0;
            				dp[q][j|(1<<p)][p] += ways;
            				if (dp[q][j|(1<<p)][p] >= MOD)
            					dp[q][j|(1<<p)][p] -= MOD;
            			}
            		} else {
            			for (int p = A[i]-1; p <= A[i]-1; p++) {
            				if ((j>>p)&1)
            					continue;
            				if (!vaild(i, k, p))
            					continue;
            				if (used[q][j|(1<<p)][p] != ucases)
            					used[q][j|(1<<p)][p] = ucases, dp[q][j|(1<<p)][p] = 0;
            				dp[q][j|(1<<p)][p] += ways;
							if (dp[q][j|(1<<p)][p] >= MOD)
            					dp[q][j|(1<<p)][p] -= MOD;
            			}
            		}
            	}
            }
        }
        
        for (int i = 0; i < n; i++) {
        	if (used[flag][(1<<n)-1][i] != ucases)
        		continue;
        	ret += dp[flag][(1<<n)-1][i];
        	ret %= MOD;
        }
        printf("%d\n", ret);
    }
    return 0;
}
/*
10
20
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
4
0 2 4 0
8
1 3 5 0 0 0 0 0
8
1 2 0 0 0 0 7 8
8
1 0 5 8 0 0 0 0
8
0 2 0 7 0 0 0 8
8
0 2 0 0 0 0 0 8
8
0 2 0 0 0 0 0 0
8
0 0 0 0 0 0 0 0
7
0 0 0 0 0 0 0
1
0
*/
