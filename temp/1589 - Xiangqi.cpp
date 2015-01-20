#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <queue>
#include <iostream>
using namespace std;

int g[16][16];
const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};

void printTable() {
    for (int i = 1; i <= 10; i++) {
        for (int j = 1; j <= 9; j++) {
            if (g[i][j] == 0)   putchar('+');
            else                putchar(g[i][j]);
        }
        puts("");
    }
    puts("-------");
}
int validPos(int x, int y) {
    return 1 <= x && x <= 10 && 1 <= y && y <= 9;
}
int checkR(int x, int y, int ex, int ey) { // Chariot
    int tx, ty;
    for (int i = 0; i < 4; i++) {
        tx = x + dx[i], ty = y + dy[i];
        while (validPos(tx, ty) && g[tx][ty] == 0) {
            if (tx == ex && ty == ey)   return 1;
            tx += dx[i], ty += dy[i];
        }
    }
    return 0;
}
int checkC(int x, int y, int ex, int ey) { // Cannon
    int tx, ty;
    for (int i = 0; i < 4; i++) {
        tx = x + dx[i], ty = y + dy[i];
        while (validPos(tx, ty) && g[tx][ty] == 0) {
            tx += dx[i], ty += dy[i];
        }
        if (validPos(tx, ty) && g[tx][ty] != 0) {
            tx = tx + dx[i], ty = ty + dy[i];
            while (validPos(tx, ty) && g[tx][ty] == 0) {
                if (tx == ex && ty == ey)   return 1;
                tx += dx[i], ty += dy[i];
            }
            if (validPos(tx, ty) && tx == ex && ty == ey)
                return 1;
        }
    }
    return 0;
}
int checkH(int x, int y, int ex, int ey) { // Horse
    static const int hx[] = {1, 1, -1, -1, 2, 2, -2, -2};
    static const int hy[] = {2, -2, 2, -2, 1, -1, 1, -1};
    static const int lx[] = {0, 0, 0, 0, 1, 1, -1, -1};
    static const int ly[] = {1, -1, 1, -1, 0, 0, 0, 0};
    int tx, ty;
    for (int i = 0; i < 8; i++) {
        tx = x + hx[i], ty = y + hy[i];
        if (tx == ex && ty == ey) {
            tx = x + lx[i], ty = y + ly[i];
            if (validPos(tx, ty) && g[tx][ty] == 0) {
                return 1;
            }
        }
    }
    return 0;
}
int check(int sx, int sy) {
    for (int i = 1; i <= 10; i++) {
        for (int j = 1; j <= 9; j++) {
            if (g[i][j] == 'R') {
                if (checkR(i, j, sx, sy))
                    return 1;
            }
            if (g[i][j] == 'C') {
                if (checkC(i, j, sx, sy))
                    return 1;
            }
            if (g[i][j] == 'G') {
                if (checkR(i, j, sx, sy))
                    return 1;
            }
            if (g[i][j] == 'H') {
                if (checkH(i, j, sx, sy))
                    return 1;
            }
        }
    }
    return 0;
}
int main() {
    int n, sx, sy, x, y;
    int tx, ty;
    char s[16];
    while (scanf("%d %d %d", &n, &sx, &sy) == 3 && n + sx + sy) {
        memset(g, 0, sizeof(g));
        for (int i = 0; i < n; i++) {
            scanf("%s %d %d", s, &x, &y);
            g[x][y] = s[0];
        }
//        printTable();
        
        int ret = 1;
        for (int i = 0; i < 4; i++) {
            tx = sx + dx[i], ty = sy + dy[i];
            if (1 <= tx && tx <= 3 && 4 <= ty && ty <= 6) {
                int tmp = g[tx][ty], r;
                g[tx][ty] = 0;
                r = check(tx, ty);
                ret &= r;
                g[tx][ty] = tmp;
            }
        }
        puts(ret ? "YES" : "NO");
    }
    return 0;
}
/*
 2 1 4
 G 10 5
 R 6 4
 
 3 1 5
 H 4 5
 G 10 5
 C 7 5
 
 0 0 0
*/