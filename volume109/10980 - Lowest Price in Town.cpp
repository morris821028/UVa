#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <sstream>
using namespace std;
int main() {
    /*freopen("in.txt", "r+t", stdin);
	freopen("out.txt", "w+t", stdout);*/
    int a, b, n, w, v, q;
    int i, j, k;
    char c;
    int cases = 0;
    while(scanf("%d.%d %d", &a, &b ,&n) == 3) {
        int m = a*100 + b;
        int dp[205] = {};
        for(i = 1; i < 205; i++)    dp[i] = 0xfffffff;
        for(i = 1; i < 205; i++) {
            dp[i] = min(dp[i], dp[i-1]+m);
        }
        for(i = 0; i < n; i++) {
            scanf("%d %d.%d", &w, &a, &b);
            v = a*100 + b;
            for(j = w; j <= 200; j++)
                dp[j] = min(dp[j], dp[j-w]+v);
        }
        for(j = 200; j >= 0; j--)
            dp[j] = min(dp[j], dp[j+1]);
        printf("Case %d:\n", ++cases);
        while(getchar() != '\n');
        string line;
        getline(cin, line);
        stringstream sin(line);
        while(sin >> q) {
            printf("Buy %d for $%d.%02d\n", q, dp[q]/100, dp[q]%100);
        }
    }
    return 0;
}
