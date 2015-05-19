#include <cstdio>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>
#include <assert.h>
#include <set>
#include <map>
#include <queue>
#include <iostream>
#include <sstream>
using namespace std;
#define MAXN 256
#define INF 0x3f3f3f3f
// 1630 - Folding
int dp[MAXN][MAXN];
char s[MAXN];
int N;
int digits(int x) {
	int ret = 0;
	while (x)
		ret++, x /= 10;
	return ret;
}
int fold(int l, int r, int c, int &f) {
    int n = r-l+1;
    if (n%c) {
        f = 0;
        return 0;
    }
    int ok = 1;
    for (int i = l; i <= r; i += c) {
        for (int j = 0; j < c && ok; j++) {
            ok &= s[i+j] == s[l+j];
        }
        if (!ok) {
            f = 0;
            return 0;
        }
    }
    f = 1;
    return digits(n/c) + 2 + dp[l][l+c-1];
}
int main() {
	int testcase;
	scanf("%d", &testcase);
    while (testcase--) {
    	scanf("%s", s);
        N = (int) strlen(s);
        for (int i = 0; i < N; i++) {
            for (int j = 0; i + j < N; j++) {
                int l = j, r = j+i;
                if (l == r) {
                    dp[l][r] = 1;
                } else {
                    dp[l][r] = r-l+1;
                    for (int k = l; k < r; k++) {
                        if (dp[l][r] > dp[l][k] + dp[k+1][r]) {
                            dp[l][r] = dp[l][k] + dp[k+1][r];
                        }
                    }
                    for (int k = l; k < r; k++) {
                        int f = 0;
                        if (digits((r-l+1)/(k-l+1)) + 2 + dp[l][l+(k-l+1)-1] >= dp[l][r])
                        	continue;
                        int t = fold(l, r, k-l+1, f);
                        if (f) {
                            dp[l][r] = min(dp[l][r], t);
                        }
                    }
                }
            }
        }
        printf("%d\n", dp[0][N-1]);
    }
    return 0;
}
/*
*/
