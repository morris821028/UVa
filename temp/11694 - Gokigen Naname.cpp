#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <assert.h>
using namespace std;
int N, ig[16][16], used[16][16] = {};
char g[16][16], ret[16][16];
int visited[16][16], cases = 0;
int isValidPos(int x, int y) {
    return 0 <= x && x < N && 0 <= y && y < N && used[x][y] == 1;
}
void printIG() {
    for (int i = 0; i <= N; i++, puts("")) {
        for (int j = 0; j <= N; j++) {
            printf("%2d ", ig[i][j]);
        }
    }
    puts("--");
}
void printRE() {
    for (int i = 0; i < N; i++, puts("")) {
        for (int j = 0; j < N; j++) {
            if (used[i][j]) {
                putchar(ret[i][j]);
            }
        }
    }
    puts("++");
}
int hasCycle(int x, int y, int px, int py, int sx, int sy) {
    
//    printf("visited %d %d, %d %d, %d %d\n", x, y, px, py, sx, sy);
    if (px >= 0 && x == sx && y == sy)  return 1;
    if (visited[x][y] == cases)         return 0;
    visited[x][y] = cases;
    if (isValidPos(x-1, y-1) && ret[x-1][y-1] == '\\') {
        if (x-1 != px || y-1 != py)
        if (hasCycle(x-1, y-1, x, y, sx, sy))
            return 1;
    }
    if (isValidPos(x, y) && ret[x][y] == '\\') {
        if (x+1 != px || y+1 != py)
        if (hasCycle(x+1, y+1, x, y, sx, sy))
            return 1;
    }
    if (isValidPos(x, y-1) && ret[x][y-1] == '/') {
        if (x+1 != px || y-1 != py)
        if (hasCycle(x+1, y-1, x, y, sx, sy))
            return 1;
    }
    if (isValidPos(x-1, y) && ret[x-1][y] == '/') {
        if (x-1 != px || y+1 != py)
        if (hasCycle(x-1, y+1, x, y, sx, sy))
            return 1;
    }
    return 0;
}
int check(int x, int y, char k) {
    if (k == '\\') {
        if ((ig[x][y] == -1 || ig[x][y] > 0) && (ig[x+1][y+1] == -1 || ig[x+1][y+1] > 0)) {
            cases++;
            ret[x][y] = k, used[x][y] = 1;
            int t = hasCycle(x, y, -1, -1, x, y);
//            if (t) {
//                puts("CYCLE");
//                printRE();
//            }
            used[x][y] = 0;
            return t == 1 ? 0 : 1;
        }
    } else {
        if ((ig[x+1][y] == -1 || ig[x+1][y] > 0) && (ig[x][y+1] == -1 || ig[x][y+1] > 0)) {
            cases++;
            ret[x][y] = k, used[x][y] = 1;
            int t = hasCycle(x, y+1, -1, -1, x, y+1);
//            if (t) {
//                puts("CYCLE");
//                printRE();
//            }
            used[x][y] = 0;
            return t == 1 ? 0 : 1;
        }
    }
    return 0;
}
void removeLink(int x, int y, char k) {
    if (k == '\\') {
        if (ig[x][y] >= 0)
            ig[x][y]--;
        if (ig[x+1][y+1] >= 0)
            ig[x+1][y+1]--;
    } else {
        if (ig[x+1][y] >= 0)
            ig[x+1][y]--;
        if (ig[x][y+1] >= 0)
            ig[x][y+1]--;
    }
}
void resumeLink(int x, int y, char k) {
    if (k == '\\') {
        if (ig[x][y] >= 0)
            ig[x][y]++;
        if (ig[x+1][y+1] >= 0)
            ig[x+1][y+1]++;
    } else {
        if (ig[x+1][y] >= 0)
            ig[x+1][y]++;
        if (ig[x][y+1] >= 0)
            ig[x][y+1]++;
    }
}
int dfs(int x, int y) {
    if (y == N)
        y = 0, x++;
    if (y == 0 && x-1 >= 0) {
        for (int i = 0; i <= N; i++)
            if (ig[x-1][i] > 0)
                return 0;
    }
    if (y-1 >= 0) {
        if (ig[x][y-1] > 0)
            return 0;
    }
    if (x == N) {
        for (int j = 0; j <= N; j++) {
            if (ig[x-1][j] > 0)
                return 0;
        }
        for (int j = 0; j <= N; j++) {
            if (ig[x][j] > 0)
                return 0;
        }
        for (int i = 0; i < N; i++, puts("")) {
            for (int j = 0; j < N; j++) {
                putchar(ret[i][j]);
            }
        }
        return 1;
    }
    if (check(x, y, '\\')) {
        removeLink(x, y, '\\');
        ret[x][y] = '\\', used[x][y] = 1;
        if (dfs(x, y+1))    return 1;
        used[x][y] = 0;
        resumeLink(x, y, '\\');
    }
    if (check(x, y, '/')) {
        removeLink(x, y, '/');
        ret[x][y] = '/', used[x][y] = 1;
        if (dfs(x, y+1))    return 1;
        used[x][y] = 0;
        resumeLink(x, y, '/');
    }
    return 0;
}
int main() {
    int testcase;
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d", &N);
        for (int i = 0; i <= N; i++)
            scanf("%s", g[i]);
        memset(used, 0, sizeof(used));
        memset(ig, 0, sizeof(ig));
        for (int i = 0; i <= N; i++) {
            for (int j = 0; j <= N; j++) {
                if (g[i][j] == '.')
                    ig[i][j] = -1;
                else
                    ig[i][j] = g[i][j] - '0';
            }
        }
        
        dfs(0, 0);
    }
    return 0;
}
/*
 2
 3
 1.1.
 ...0
 .3..
 ..2.
 5
 .21...
 ..33.0
 ......
 ..33..
 0..33.
 ....11
*/