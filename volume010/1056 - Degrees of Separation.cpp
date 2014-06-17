#include <stdio.h>
#include <iostream>
#include <map>
#define oo 0xffff
using namespace std;

int main() {
    int n, m, cases = 0, i, j, k;
    char a[50], b[50];
    while(scanf("%d %d", &n, &m) == 2) {
        if(n == 0 && m == 0)
            break;
        int g[51][51], x, y;
        for(i = 1; i <= n; i++) {
            for(j = 1; j <= n; j++)
                g[i][j] = oo;
            g[i][i] = 0;
        }
        map<string, int> R;
        map<string, int>::iterator it;
        int size = 0;
        while(m--) {
            scanf("%s %s", a, b);
            it = R.find(a);
            if(it == R.end())
                R[a] = ++size, x = size;
            else    x = it->second;
            it = R.find(b);
            if(it == R.end())
                R[b] = ++size, y = size;
            else    y = it->second;
            g[x][y] = g[y][x] = 1;
        }
        for(k = 1; k <= n; k++) {
            for(i = 1; i <= n; i++) {
                for(j = 1; j <= n; j++) {
                    if(g[i][j] > g[i][k] + g[k][j])
                        g[i][j] = g[i][k] + g[k][j];
                }
            }
        }
        int mx = 0;
        for(i = 1; i <= n; i++)
            for(j = 1; j <= n; j++)
                if(g[i][j] > mx)
                    mx = g[i][j];
        printf("Network %d: ", ++cases);
        if(mx == oo)
            puts("DISCONNECTED");
        else
            printf("%d\n", mx);
        puts("");
    }
    return 0;
}
