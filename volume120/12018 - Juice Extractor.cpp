#include <stdio.h>
#include <algorithm>
#include <queue>
using namespace std;
struct E {
    int l, r;
    bool operator<(const E &a) const {
        if(l != a.l)
            return l < a.l;
        return r < a.r;
    }
};
int main() {
	int t, n, i, j;
	int cases = 0;
	scanf("%d", &t);
	E D[1005];
	while(t--) {
		scanf("%d", &n);
        for(i = 1; i <= n; i++)
            scanf("%d %d", &D[i].l, &D[i].r);
        sort(D+1, D+1+n);
        int dp[1005] = {}, ret = 0;
        for(i = 1; i <= n; i++) {
            int combo = 0;
            if(i != n && D[i].l == D[i+1].l)
                continue;
            for(j = i; j >= 1; j--) {
                if(D[j].r >= D[i].l)
                    combo++;
                if(combo >= 3)
                    dp[i] = max(dp[i], dp[j-1]+combo);
                else
                    dp[i] = max(dp[i], dp[j-1]);
            }
            ret = max(ret, dp[i]);
        }
        printf("Case #%d: %d\n", ++cases, ret);
	}
    return 0;
}
/*
20
20
48 69
33 76
27 62
2 9
42 63
10 24
0 15
13 54
10 52
40 48
45 55
17 35
22 52
42 78
27 42
44 58
39 68
17 61
42 64
29 69
*/
