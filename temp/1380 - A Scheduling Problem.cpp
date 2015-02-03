#include <cstdio>
#include <cstring>
#include <vector>
#include <complex>
#include <cmath>
#include <algorithm>
#include <assert.h>
#include <set>
#include <map>
#include <queue>
using namespace std;
#define MAXN 256
#define INF 0x3f3f3f3f
vector<int> g[MAXN];
int dg[MAXN][MAXN];
pair<int, int> dfs(int u, int p, int day) {
    int up = 0, down = 0;
    vector< pair<int, int> > D;
    for (int i = 0; i < g[u].size(); i++) {
        int v = g[u][i];
        if (v == p) continue;
        pair<int, int> t = dfs(v, u, day);
        if (dg[u][v] == 2)
            D.push_back(t);
        else if (dg[u][v] == 1)
            down = max(down, t.second + 1);
        else
            up = max(up, t.first + 1);
    }
    if (D.size() > 0) {
        sort(D.begin(), D.end());
        int tup = INF, tdown = INF;
        for (int i = 0; i <= D.size(); i++) {
            int u = i - 1 >= 0 ? D[i-1].first + 1 : 0, d = 0;
            for (int j = i; j < D.size(); j++)
                d = max(d, D[j].second + 1);
            u = max(u, up), d = max(d, down);
            if (u + d <= day)
                tup = min(tup, u), tdown = min(tdown, d);
        }
        up = tup, down = tdown;
    }
//    printf("%d : %d %d\n", u, up, down);
    if (up + down <= day)
        return make_pair(up, down);
    else
        return make_pair(INF, INF);
}
int test(int day) {
//    printf("day %d -----\n", day);
    pair<int, int> t = dfs(1, -1, day);
    return t.first + t.second <= day;
}
int main() {
    int x, y;
    char s[MAXN];
    while (true) {
        for (int i = 0; i < MAXN; i++)
            g[i].clear();
        int f = 0;
        while (scanf("%d", &x) == 1 && x) {
            f++;
            while (scanf("%s", s) == 1 && s[0] != '0') {
                int n = (int) strlen(s);
                if (s[n-1] == 'd') {
                    s[n-1] = '\0';
                    sscanf(s, "%d", &y);
                    g[x].push_back(y), g[y].push_back(x);
                    dg[x][y] = 1, dg[y][x] = 0;
                } else if (s[n-1] == 'u') {
                    s[n-1] = '\0';
                    sscanf(s, "%d", &y);
                    g[x].push_back(y), g[y].push_back(x);
                    dg[x][y] = 0, dg[y][x] = 1;
                } else {
                    sscanf(s, "%d", &y);
                    g[x].push_back(y), g[y].push_back(x);
                    dg[x][y] = 2, dg[y][x] = 2;
                }
            }
        }
        if (!f) break;
        int ret = 0, l = 0, r = MAXN, mid;
        while (l <= r) {
            mid = (l + r)/2;
            if (test(mid))
                r = mid - 1, ret = mid;
            else
                l = mid + 1;
        }
        printf("%d\n", ret + 1);
    }
    return 0;
}
/*
 1 2 3d 0
 2 4d 0
 3 5d 0
 4 6d 0
 0
*/