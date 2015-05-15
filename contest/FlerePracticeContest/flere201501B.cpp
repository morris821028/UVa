#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <queue>
#include <iostream>
#include <assert.h>
using namespace std;
#define MAXN 32767

long long P[MAXN], C[MAXN];
int main() {
    int testcase, N;
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d", &N);
        for (int i = 1; i <= N; i++)
            scanf("%lld", &P[i]);
        for (int i = 1; i < N; i++)
            scanf("%lld", &C[i]);
        long long day = 0, mx = 0, earn = 0;
        for (int i = 1; i < N; i++) {
            mx = max(mx, P[i]);
            if (earn >= C[i]) {
                earn -= C[i];
            } else {
                long long t = ((C[i]-earn) /mx) + ((C[i]-earn)%mx != 0);
                day += t;
                earn = earn + t * mx - C[i];
            }
        }
        printf("%lld\n", day);
    }
    return 0;
}
/*
 3
 3
 10 1 5 
 1 30
 3
 1 10 5 
 10 30 
 2
 1 100
 1000
 */