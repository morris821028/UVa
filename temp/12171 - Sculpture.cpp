#include <stdio.h>
#include <map>
#include <queue>
using namespace std;
#define MAXN 128
#define MAX_BOUND 1024
int used[MAXN][MAXN][MAXN] = {}, visited[MAXN][MAXN][MAXN] = {};
void mapRelabel(map<int, int> &R, int val[]) {
    int size = 0;
    for (map<int, int>::iterator it = R.begin();
         it != R.end(); it++) {
        val[size] = it->first;
        it->second = size++;
    }
}
int main() {
    int n, cases = 0, testcase;
    int lx[MAXN], ly[MAXN], lz[MAXN];
    int rx[MAXN], ry[MAXN], rz[MAXN];
    int xval[MAXN], yval[MAXN], zval[MAXN];
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d", &n);
        cases++;
        map<int, int> RX, RY, RZ;
        for (int i = 0; i < n; i++) {
            scanf("%d %d %d", &lx[i], &ly[i], &lz[i]);
            scanf("%d %d %d", &rx[i], &ry[i], &rz[i]);
            rx[i] += lx[i], ry[i] += ly[i], rz[i] += lz[i];
            RX[lx[i]] = RX[rx[i]] = 1;
            RY[ly[i]] = RY[ry[i]] = 1;
            RZ[lz[i]] = RZ[rz[i]] = 1;
        }
        RX[0] = RY[0] = RZ[0] = 1;
        RX[MAX_BOUND] = RY[MAX_BOUND] = RZ[MAX_BOUND] = 1;
        mapRelabel(RX, xval);
        mapRelabel(RY, yval);
        mapRelabel(RZ, zval);
        int a = (int) RX.size(), b = (int) RY.size(), c = (int) RZ.size();
        int sx, ex, sy, ey, sz, ez;
        for (int i = 0; i < n; i++) {
            sx = RX[lx[i]], ex = RX[rx[i]];
            sy = RY[ly[i]], ey = RY[ry[i]];
            sz = RZ[lz[i]], ez = RZ[rz[i]];
            for (int p = sx; p < ex; p++) {
                for (int q = sy; q < ey; q++) {
                    for (int r = sz; r < ez; r++) {
                        used[p][q][r] = cases;
                    }
                }
            }
        }
        // bfs
        int retV = MAX_BOUND * MAX_BOUND * MAX_BOUND, retP = 0;
        const int dx[] = {0, 0, 1, -1, 0, 0};
        const int dy[] = {1, -1, 0, 0, 0, 0};
        const int dz[] = {0, 0, 0, 0, 1, -1};
        queue<int> X, Y, Z;
        X.push(0), Y.push(0), Z.push(0), visited[0][0][0] = cases;
        while (!X.empty()) {
            sx = X.front(), X.pop();
            sy = Y.front(), Y.pop();
            sz = Z.front(), Z.pop();
            retV -= (xval[sx+1] - xval[sx])*(yval[sy+1] - yval[sy])*(zval[sz+1] - zval[sz]);
            for (int i = 0; i < 6; i++) {
                ex = sx + dx[i], ey = sy + dy[i], ez = sz + dz[i];
                if (ex < 0 || ex >= a - 1 || ey < 0 || ey >= b - 1 || ez < 0 || ez >= c - 1)
                    continue;
                if (used[ex][ey][ez] != cases && visited[ex][ey][ez] != cases) {
                    visited[ex][ey][ez] = cases;
                    X.push(ex), Y.push(ey), Z.push(ez);
                }
                if (used[ex][ey][ez] == cases) {
                    if (i < 2) {
                        retP += (xval[sx+1] - xval[sx])*(zval[sz+1] - zval[sz]);
                    } else if (i < 4) {
                        retP += (yval[sy+1] - yval[sy])*(zval[sz+1] - zval[sz]);
                    } else if (i < 6) {
                        retP += (xval[sx+1] - xval[sx])*(yval[sy+1] - yval[sy]);
                    }
                }
            }
        }
        printf("%d %d\n", retP, retV);
    }
    return 0;
}
/*
 2
 7
 1 1 1 5 5 1
 1 1 10 5 5 1
 1 1 2 1 4 8
 2 1 2 4 1 8
 5 2 2 1 4 8
 1 5 2 4 1 8
 3 3 4 1 1 1
 2
 1 2 3 3 4 5
 6 2 3 3 4 5
*/