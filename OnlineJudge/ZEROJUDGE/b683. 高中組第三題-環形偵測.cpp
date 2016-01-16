#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;
char g[64][64];
int used[64][64] = {};
int n, m;
const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};
int countadj(int x, int y, int &rx, int &ry) {
    int tx, ty, has = 0;
    for (int k = 0; k < 4; k++) {
        tx = x + dx[k], ty = y + dy[k];
        if (tx < 0 || ty < 0 || tx >= n || ty >= m)
            continue;
        if (g[tx][ty] == '.' && used[tx][ty] == 0)
            has++, rx = tx, ry = ty;
    }
    return has;
}
int main() {
    while (scanf("%d %d", &n, &m) == 2) {
        for (int i = 0; i < n; i++)
            scanf("%s", g[i]);
        memset(used, 0, sizeof(used));
        unsigned long long retn, rets, retp;
        retn = 0, rets = 0, retp = 1;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (g[i][j] == '.' && used[i][j] == 0) {
                    int x = i, y = j, tx, ty;
                    int cnt = 0, valid = 0;
                    vector< pair<int, int> > A;
                    while (true) {
                        int has = 0, rx = ty, ry = tx;
                        has = countadj(x, y, rx, ry);
                        if (has == 0) {
                            if (cnt >= 4)
                            for (int k = 0; k < 4; k++) {
                                tx = x + dx[k], ty = y + dy[k];
                                if (tx == i && ty == j) {
                                    cnt++;
                                    retn++, rets += cnt, retp *= cnt;
                                    valid = 1;
                                }
                            }
                            break;
                        }
                        if (cnt != 0 && has != 1)
                            break;
                        if (cnt == 0 && has != 2)
                            break;
                        used[x][y] = 1;
                        A.push_back({x, y});
                        x = rx, y = ry, cnt++;
                    }
                    if (!valid) {
                        for (int k = 0; k < A.size(); k++)
                            used[A[k].first][A[k].second] = 0;
                    }
                }
            }
        }
        printf("%llu %llu %llu\n", retn, rets, retp);
    }
    return 0;
}
/*
 3 3
 ...
 .#.
 ...
 5 6
 ######
 ...#..
 .#.###
 ...#.#
 ####.#
 11 7
 .......
 .#####.
 .#...#.
 .#.#.#.
 .#...#.
 .#####.
 .......
 #######
 #....#.
 ..##.#.
 .###...
*/