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

char g[16][16], pattern[16][16];

int isprime(int n) {
    for (int i = 2; i * i <= n; i++)
        if (n%i == 0)
            return 0;
    return 1;
}

int n, m, pn;
pair<int, int> stars[32], pstar[32];
const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};
int bfs(int sx, int sy) {
    queue<int> X, Y;
    int used[16][16] = {}, tx, ty;
    int ret = 0;
    X.push(sx), Y.push(sy), used[sx][sy] = 1;
    while (!X.empty()) {
        sx = X.front(), X.pop();
        sy = Y.front(), Y.pop();
        ret++;
        for (int i = 0; i < 4; i++) {
            tx = sx + dx[i], ty = sy + dy[i];
            if (tx < 0 || ty < 0 || tx >= n || ty >= n)
                continue;
            if (used[tx][ty])
                continue;
            if (pattern[tx][ty] == '*' && g[tx][ty] == '*') {
                used[tx][ty] = 1;
                X.push(tx), Y.push(ty);
            }
        }
    }
    return ret;
}

int check(int m) {
    int used[16][16] = {}, tx, ty;
    char c = 'A';
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (g[i][j] == '*' && used[i][j] == 0) {
                for (int p = 0; p < m; p++) {
                    tx = i + pstar[p].first - pstar[0].first;
                    ty = j + pstar[p].second - pstar[0].second;
                    if (tx < 0 || ty < 0 || tx >= n || ty >= n)
                        return 0;
                    if (used[tx][ty] || g[tx][ty] != '*')
                        return 0;
                    used[tx][ty] = c;
                }
                c++;
            }
        }
    }
    for (int i = 0; i < n; i++, puts("")) {
        for (int j = 0; j < n; j++) {
            if (used[i][j])
                printf("%c", used[i][j]);
            else
                printf(".");
        }
    }
    puts("");
    return 1;
}
int main() {
    while (scanf("%d", &n) == 1 && n) {
        for (int i = 0; i < n; i++)
            scanf("%s", g[i]);
        memcpy(pattern, g, sizeof(g));
        m = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (g[i][j] == '*')
                    stars[m++] = make_pair(i, j);
            }
        }
        if (isprime(m)) {
            int c = 'A';
            for (int i = 0; i < n; i++, puts("")) {
                for (int j = 0; j < n; j++) {
                    if (g[i][j] == '*')
                        g[i][j] = c, c++;
                    printf("%c", g[i][j]);
                }
            }
            puts("");
            continue;
        }
        
        int ok = 0;
        for (int i = 2; i <= m && !ok; i++) { // the number of pieces
            if (m%i == 0) {
                int c[32] = {};
                for (int j = 0; j < m - m/i; j++)
                    c[j] = 1;
                sort(c, c+m);
//                printf("the number of piece %d\n", i);
                do {
                    pn = 0;
                    for (int j = 0; j < m; j++) {
                        if (!c[j]) {
                            pattern[stars[j].first][stars[j].second] = '*';
                            pstar[pn++] = stars[j];
                        } else {
                            pattern[stars[j].first][stars[j].second] = '.';
                        }
                    }
                    if (bfs(pstar[0].first, pstar[0].second) == m/i) {
//                        for (int j = 0; j < n; j++) {
//                            printf("%s\n", pattern[j]);
//                        }
//                        puts("");
                        if (check(pn)) {
                            ok = 1;
                            break;
                        }
                    }
                } while (next_permutation(c, c + m) && c[0] == 0);
            }
        }
    }
    return 0;
}
/*
 5
 ..**.
 .****
 ****.
 .**..
 .....
 2
 **
 **
 2
 **
 .*
 0
 */