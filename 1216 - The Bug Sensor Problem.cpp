#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <string.h>
#include <math.h>
using namespace std;
int x[1000], y[1000];
struct E {
    int x, y;
    long long v;
    E(int a, int b, long long c):
        x(a), y(b), v(c) {}
    E():
        x(0), y(0), v(0) {}
    bool operator<(const E &a) const {
        return  v < a.v;
    }
};
E D[1000000];
int p[1000], rank[1000];
int findp(int x) {
    return p[x] == x ? x : (p[x]=findp(p[x]));
}
int joint(int x, int y) {
    x = findp(x), y = findp(y);
    if(x == y)
        return 0;
    if(rank[x] > rank[y])
        rank[x] += rank[y], p[y] = x;
    else
        rank[y] += rank[x], p[x] = y;
    return 1;
}
int main() {
    int testcase;
    int i, j;
    scanf("%d", &testcase);
    while(testcase--) {
        int n, m, e;
        scanf("%d", &n);
        m = 0, e = 0;
        while(scanf("%d", &x[m]) == 1 && x[m] != -1)
            scanf("%d", &y[m]), m++;
        for(i = 0; i < m; i++)
            for(j = i+1; j < m; j++)
                D[e++] = E(i, j, ((long long)x[i]-x[j])*(x[i]-x[j])+((long long)y[i]-y[j])*(y[i]-y[j]));
        sort(D, D+e);
        for(i = 0; i < m; i++)
            p[i] = i, rank[i] = 1;
        int component = m;
        for(i = 0; i < e; i++) {
            if(joint(D[i].x, D[i].y))
                component--;
            if(component <= n) {
                printf("%.0lf\n", ceil(sqrt(D[i].v)));
                break;
            }
        }
    }
    return 0;
}
