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
using namespace std;

#define MAXN 1024
const long long mod = 1000000007LL;
long long f[MAXN], invf[MAXN];
vector<int> g[MAXN];
long long dfs(int u, int &size) {
    vector<int> subtree;
    long long ret = 1;
    int sum = 0;
    
    for (int i = 0; i < g[u].size(); i++) {
        int v = g[u][i], w;
        ret = (ret * dfs(v, w))%mod;
        subtree.push_back(w), sum += w;
    }
    size = 1 + sum;
    ret = (ret * f[sum])%mod; // * n!
    for (int i = 0; i < subtree.size(); i++)
        ret = (ret * invf[subtree[i]])%mod; // / a!
    return ret;
}
long long mpow(long long x, long long y, long long mod) {
    long long ret = 1;
    while (y) {
        if (y&1)
            ret = (ret * x)%mod;
        x = (x * x)%mod, y >>= 1;
    }
    return ret;
}
int main() {
    f[0] = 1, invf[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        f[i] = (f[i - 1] * i)%mod;
        invf[i] = mpow(f[i], mod - 2, mod);
    }
    
    int testcase, cases = 0, n;
    int a, b;
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            g[i].clear();
        }
        
        int indeg[MAXN] = {}, root = 0, w;
        for (int i = 1; i < n; i++) {
            scanf("%d %d", &a, &b);
            g[a].push_back(b);
            indeg[b]++;
        }
        for (int i = 1; i <= n; i++) {
            if (indeg[i] == 0) {
                root = i;
            }
        }
        long long ret = dfs(root, w);
        printf("Case %d: %lld\n", ++cases, ret);
    }
    return 0;
}
/*
 9 9
 2 7
 3 5
 6 8
 5 6
 2 8
 2 6
 0 2
 7 9
 2 8
 
 18 9
 8 15
 1 17
 0 10
 9 18
 12 15
 1 5
 5 6
 0 10
 11 17
 
 8 7
 0 3
 2 5
 5 8
 1 3
 3 6
 4 6
 0 2
 1 1
 0 1
 2 1
 0 1
 0 0
 */