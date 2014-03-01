#include <stdio.h>
#include <map>
#include <iostream>
using namespace std;
int r[5005], p[5005];
int findp(int x) {
    return p[x] == x ? x : p[x] = findp(p[x]);
}
void joint(int x, int y) {
    x = findp(x);
    y = findp(y);
    if(x != y) {
        p[x] = y;
        r[y] += r[x];
    }
}
int main() {
    int C, R, i, j, k;
    char cmd[105];
    while(scanf("%d %d", &C, &R) == 2 && C) {
        map<string, int> M;
        for(i = 0; i < C; i++) {
            scanf("%s", cmd), M[cmd] = i;
            r[i] = 1, p[i] = i;
        }
        for(i = 0; i < R; i++) {
            scanf("%s", cmd);
            j = M[cmd];
            scanf("%s", cmd);
            k = M[cmd];
            joint(j, k);
        }
        int ans = 0;
        for(i = 0; i < C; i++)
            if(r[i] > ans)
                ans = r[i];
        printf("%d\n", ans);
    }
    return 0;
}
