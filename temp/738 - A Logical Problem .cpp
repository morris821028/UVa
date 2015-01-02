#include <stdio.h>
#include <string.h>
#include <map>
#include <set>
#include <queue>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <assert.h>
using namespace std;
#define INF 0x3f3f3f3f
#define MAXN 512
char g[MAXN][MAXN], val[MAXN];
int n;
int validPos(int x, int y) {
    return x >= 0 && x < MAXN && y >= 0 && y < MAXN;
}
int query(int x, int y, int dir, char pre) {
    if (g[x][y] == '?')
        return query(x, y - 1, 2, '?');
    if (g[x][y] >= 'A' && g[x][y] <= 'Z')
        return val[g[x][y] - 'A'] - '0';
    if (g[x][y] == 'o')
        return !query(x, y - 1, 2, 'o');
    if (g[x][y] == ')')
        return query(x - 1, y - 3, 2, ')') && query(x + 1, y - 3, 2, ')');
    if (g[x][y] == '>')
        return query(x - 1, y - 3, 2, '>') || query(x + 1, y - 3, 2, '>');
    if (g[x][y] == '-') {
        if (dir == 2)
            return query(x, y - 1, 2, '-');
        if (dir == 3)
            return query(x, y + 1, 3, '-');
        assert(false);
    }
    if (g[x][y] == '|') {
        if (dir == 0)
            return query(x - 1, y, 0, '|');
        if (dir == 1)
            return query(x + 1, y, 1, '|');
        assert(false);
    }
    if (g[x][y] == '+') {
        if (dir != 1 && validPos(x-1, y) && g[x-1][y] == '|')
            return query(x - 1, y, 0, '|');
        if (dir != 0 && validPos(x+1, y) && g[x+1][y] == '|')
            return query(x + 1, y, 1, '|');
        if (dir != 3 && validPos(x, y-1) && g[x][y-1] == '-')
            return query(x, y - 1, 2, '-');
        if (dir != 2 && validPos(x, y+1) && g[x][y+1] == '-')
            return query(x, y + 1, 3, '-');
        assert(false);
    }
    assert(g[x][y] == ' ' && pre != '?');
    return 0;
}
int main() {
    memset(g, ' ', sizeof(g));
    while (gets(g[0])) {
        int qx = -1, qy = -1;
        for (n = 1; gets(g[n]) && g[n][0] != '*'; n++);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < MAXN; j++) {
                if (g[i][j] == '?') {
                    qx = i, qy = j;
                }
            }
        }
        
        int dir = -1;
        if (validPos(qx-1, qy) && g[qx-1][qy] == '|')
        	qx--, dir = 0;
        else if (validPos(qx+1, qy) && g[qx+1][qy] == '|') 
        	qx++, dir = 1;
        else if (validPos(qx, qy-1) && g[qx][qy-1] == '-') 
        	qy--, dir = 2;
        else if (validPos(qx, qy+1) && g[qx][qy+1] == '-') 
        	qy++, dir = 3;
        assert(qx >= 0 && qy >= 0);
        while (scanf("%s", val) == 1 && val[0] != '*')
            printf("%d\n", query(qx, qy, dir, '?'));
        puts("");
        memset(g, ' ', sizeof(g));
        while (getchar() != '\n');
    }
    return 0;
}
/*
A-:\
  : )-?
B-:/
*
00000000000000000000000000
10000000000000000000000000
01000000000000000000000000
11000000000000000000000000
*
  +-A
  |
  +-:\
    : >o-:\
  +-:/   : )-?
  |+----o:/
B-+|
 C-+
*
00000000000000000000000000
11100000000000000000000000
*
A-:\
  : )-?
A-:/
*
00000000000000000000000000
10000000000000000000000000
*
A-o:\
   : )o-?
A-o:/
*
00000000000000000000000000
10000000000000000000000000
*
        ? 
A-o:\   | 
   : )o-+
A-o:/
*
00000000000000000000000000
10000000000000000000000000
*
 */
