#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string.h>
#include <algorithm>
#include <queue>
#include <stack>

using namespace std;

int parent[1024], weight[1024];
int deg[1024];
int findp(int x) {
    return parent[x] == x ? x : parent[x] = findp(parent[x]);
}
int joint(int x, int y) {
    x = findp(x), y = findp(y);
    if (x == y)
        return 0;
    if (weight[x] > weight[y])
        weight[x] += weight[y], parent[y] = x;
    else
        weight[y] += weight[x], parent[x] = y;
    return 1;
}
int main() {
    int cases = 0;
    int N, M, T, x, y;
    while (scanf("%d %d %d", &N, &M, &T) == 3 && N+M+T) {
        for (int i = 1; i <= N; i++)
            parent[i] = i, weight[i] = 1, deg[i] = 0;
        
        int component = N;
        for (int i = 0; i < M; i++) {
            scanf("%d %d", &x, &y);
            deg[x]++, deg[y]++;
            if (joint(x, y))
                component--;
        }
        
        for (int i = 1; i <= N; i++) {
            if (weight[i] == 1 && findp(i) == i)
                component--;
        }
        int ret = M, odd[1024] = {};
        ret += component > 0 ? component - 1 : 0;
        for (int i = 1; i <= N; i++) {
            if (deg[i]&1)
                odd[findp(i)]++;
        }
        for (int i = 1; i <= N; i++) {
            if (odd[i] >= 4)
                ret += odd[i]/2 - 1;
        }
        printf("Case %d: %d\n", ++cases, ret * T);
    }
    return 0;
}

/*
 5 3 1
 1 2
 1 3
 4 5
 
 4 4 1
 1 2
 1 4
 2 3
 3 4
 0 0 0
 */