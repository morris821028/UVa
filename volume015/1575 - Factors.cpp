#include <stdio.h>
#include <math.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <string.h>
#include <assert.h>
#include <map>
using namespace std;

const long long MAX_INT64 = ~0ULL>>1;
int path[64];
long long P[20] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 51, 53};
long long C[64][64] = {};
map<long long, long long> F;
void build(int idx, long long n, long long limit) {
    long long ways = 1, items = 0;
    for (int i = 0; i < idx; i++)
        items += path[i];
    for (int i = 0; i < idx; i++) {
        long long t = C[items][path[i]];
        if (MAX_INT64 / ways < t) { // ways * t > MAX_INT64
            ways = -1;
            break;
        }
        ways *= t, items -= path[i];
    }
    if (ways != -1) {
        long long &ret = F[ways];
        if (ret == 0)   ret = n;
        else            ret = min(ret, n);
    }
        
    for (int i = 1; ; i++) {
        limit /= P[idx];
        if (limit == 0) break;
        path[idx] = i, n *= P[idx];
        build(idx+1, n, limit);
        
    }
}
int main() {
    C[0][0] = 1;
    for (int i = 1; i < 64; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++)
            C[i][j] = C[i-1][j] + C[i-1][j-1];
    }
    build(0, 1, MAX_INT64);
    F[1] = 2;
    long long n;
    while (scanf("%lld", &n) == 1) {
        printf("%lld %lld\n", n, F[n]);
    }
    return 0;
}
/*
 1
 2
 3
 105
 */