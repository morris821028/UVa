#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#include <sstream>
using namespace std;
int g[20][40][40];
int v[50], path[40], used[40];
int t, n, m;
void dfs(int st, int ed, int dep, int k) {
    int i;
    if(st == ed) {
        for(i = 0; i < dep-1; i++) {
            v[path[i]]++;
        }
        return ;
    }
    for(i = 1; i <= m; i++) {
        if(g[k][st][i] && used[i] == 0) {
            path[dep] = i;
            used[i] = 1;
            dfs(i, ed, dep+1, k);
            used[i] = 0;
        }
    }
}
int main() {
    char s[100], c;
    int i, j, k, x, y;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        while(getchar() != '\n');
        m = 0;
        memset(g, 0, sizeof(g));
        int gg[105][105] = {};
        for(i = 0; i < n; i++) {
            string s, token;
            getline(cin, s);
            stringstream sin(s);
            while(sin >> token) {
                stringstream in(token);
                in >> x >> c >> y;
                gg[x][y]++;
                gg[y][x]++;
                g[i][x][y] = 1;
                g[i][y][x] = 1;
                m = max(m, x);
                m = max(m, y);
            }
        }
        int acc = 1;
        for(i = 1; i <= m; i++) {
            for(j = i+1; j <= m; j++) {
                memset(v, 0, sizeof(v));
                for(k = 0; k < n; k++) {
                    used[i] = 1;
                    dfs(i, j, 0, k);
                    used[i] = 0;
                }
                if(gg[i][j] > 1) acc = 0;
                for(k = 0; k <= m; k++)
                    if(v[k] > 1)
                        break;
                if(k != m+1)
                    acc = 0, i = m+1, j = m+1;
            }
        }
        puts(acc ? "YES" : "NO");
    }
    return 0;
}
/*
4
4
1-2 1-3 1-4 1-5 5-6 5-7 5-8
2-3 2-4 2-5 2-6 6-1 6-7 6-8
3-4 3-7 3-5 3-6 7-8 7-1 7-2
4-8 4-5 4-6 4-7 8-1 8-2 8-3
2
1-5 2-3 2-4 4-5 4-6
1-3 1-4 1-6 2-6 3-5
2
1-5 2-3 2-4 4-5 4-6
1-3 1-6 4-6 2-6 3-5
2
1-5 2-3 2-4 4-5 4-6
2-5 1-3 2-6 4-1 3-6
*/
