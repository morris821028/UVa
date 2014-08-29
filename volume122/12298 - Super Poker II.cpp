#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string.h>
#include <algorithm>
#include <queue>
#include <stack>
#include <math.h>
#include <iostream>
#include <map>
#include <complex>
#include <cmath>
using namespace std;

// this problem
#define maxL (50000>>5)+1
#define GET(x) (mark[x>>5]>>(x&31)&1)
#define SET(x) (mark[x>>5] |= 1<<(x&31))
int mark[maxL];
void sieve() {
    register int i, j, k;
    SET(1);
    int n = 50000;
    for(i = 2; i <= n; i++) {
        if(!GET(i)) {
            for(k = n/i, j = i*k; k >= i; k--, j -= i)
                SET(j);
        }
    }
}

int lost[4][65536];
int getSuit(char c) {
    static char s[] = "SHCD";
    return (int)(find(s, s+4, c) - s);
}

int isprime(int x) {
    return !GET(x);
}
int main() {
    sieve();
    int a, b, n, x;
    char suit;
    while (scanf("%d %d %d", &a, &b, &n) == 3 && a + b + n) {
        memset(lost, 0, sizeof(lost));
        for (int i = 0; i < n; i++) {
            scanf("%d%c", &x, &suit);
            lost[getSuit(suit)][x] = 1;
        }
        
        long long dp[4][65536] = {};
        for (int i = 0; i < 4; i++) {
            for (int j = b; j >= 4; j--) {
                if (!isprime(j) && !lost[i][j]) {
                    if (i == 0)
                        dp[i][j] = 1;
                    else {
                        for (int k = b - j; k >= 0; k--) {
                            dp[i][k + j] += dp[i-1][k];
                        }
                    }
                }
            }
        }
        for (int i = a; i <= b; i++) {
            printf("%lld\n", dp[3][i]);
        }
        puts("");
    }
    return 0;
}
/*
 12 20 2
 4S 6H
 0 0 0
 */