#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <queue>
#include <iostream>
using namespace std;
#define MAXN 10005
int main() {
    int n, m, x;
    int u, v, cases = 0;
    while (scanf("%d %d", &n, &m) == 2 && n) {
        int ban[10] = {};
        for (int i = 0; i < m; i++) {
            scanf("%d", &x);
            ban[x] = 1;
        }
        queue<int> Q;
        int used[MAXN] = {}, from[MAXN][2], ok = 0;
        for (int i = 1; i <= 9; i++) {
            if (used[i%n] == 0 && !ban[i]) {
                used[i%n] = 1;
                from[i%n][0] = -1, from[i%n][1] = i;
                Q.push(i%n);
            }
        }
        
        printf("Case %d: ", ++cases);
        while (!Q.empty()) {
            u = Q.front(), Q.pop();
            for (int i = 0; i <= 9; i++) {
                v = (u * 10 + i)%n;
                if (used[v] == 0 && !ban[i]) {
                    used[v] = 1;
                    from[v][0] = u, from[v][1] = i;
                    Q.push(v);
                }
            }
            if (used[0]) {
                ok = 1;
                u = 0;
                string ret = "";
                while (u >= 0) {
                    ret = (char)(from[u][1] + '0') + ret;
                    u = from[u][0];
                }
                printf("%s\n", ret.c_str());
                break;
            }
        }
        if (!ok)    puts("-1");
    }
    return 0;
}
/*
 2345 3
 7 8 9
 100 1
 0
*/