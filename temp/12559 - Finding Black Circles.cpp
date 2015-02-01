#include <cstdio>
#include <cstring>
#include <vector>
#include <complex>
#include <cmath>
#include <algorithm>
#include <assert.h>
#define MAXR 128
#define MAXN 256
#define eps 1e-6
#define MAXMN 65536
using namespace std;

char circlePattern[MAXR][MAXN][MAXN], T[MAXN][MAXN];
int circleW[MAXR], circleH[MAXR], circlePixel[MAXR];
vector< pair<int, int> > cVec[MAXR];
void printCircle(int r) {
    const double dx[] = {0, 0, 1, 1, 1, -1, -1, -1};
    const double dy[] = {1, -1, 0, 1, -1, 0, 1, -1};
    double x, y;
    double cx = r, cy = r;
    circleW[r] = circleH[r] = 2 * r + 1, circlePixel[r] = 0;
    for (int i = 0; i <= 2 * r; i++) {
        for (int j = 0; j <= 2 * r; j++) {
            int in = 0, out = 0;
            for (int k = 0; k < 8; k++) {
                x = i + dx[k]/2, y = j + dy[k]/2;
                if (pow(x - cx, 2) + pow(y - cy, 2) < r*r - eps) {
                    in = 1;
                }
                if (pow(x - cx, 2) + pow(y - cy, 2) > r*r - eps) {
                    out = 1;
                }
            }
            if (in&out)
                cVec[r].push_back(make_pair(i, j));
            circlePixel[r] += in&out;
            circlePattern[r][i][j] = (in&out) ? '1' : '0';
        }
        circlePattern[r][i][2 * r + 1] = '\0';
    }
}

struct Pos {
    int x, y, r;
    Pos(int a = 0, int b = 0, int c = 0):
    x(a), y(b), r(c) {}
    bool operator<(const Pos &a) const {
        if (r != a.r)   return r < a.r;
        if (y != a.y)   return y < a.y;
        return x < a.x;
    }
};
int main() {
    for (int i = 5; i < MAXR; i++)
        printCircle(i);
    int testcase, cases = 0;
    int m, n, p, q;
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d %d", &n, &m);
        for (int i = 0; i < m; i++)
            scanf("%s", T[i]);
        vector<Pos> ret;
        
        int rrr = min(n, m);
        for (int ir = 5; ir <= rrr; ir++) {
            p = circleH[ir], q = circleW[ir];
            int qx = m - p;
            int qy = n - q;
            for(int i = 0; i <= qx; i++)    {
                for(int j = 0; j <= qy; j++) {
                    int c = 0;
                    for (int k = 0; k < cVec[ir].size(); k++) {
                        int x = cVec[ir][k].first, y = cVec[ir][k].second;
                        if (T[i+x][j+y] == '1')
                            c++;
                    }
                    if (c >= circlePixel[ir] * 0.7) {
                        ret.push_back(Pos(i + ir, j + ir, ir));
                    }
                }
            }
        }
        printf("Case %d: %d", ++cases, (int) ret.size());
        sort(ret.begin(), ret.end());
        for (int i = 0; i < ret.size(); i++)
            printf(" (%d,%d,%d)", ret[i].r, ret[i].y, ret[i].x);
        puts("");
    }
    return 0;
}