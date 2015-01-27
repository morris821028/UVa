// simiar UVa 12795 - Ecology 
#include <stdio.h>
#include <vector>
#include <map>
#include <algorithm>
#include <set>
#include <string.h>
#include <assert.h>
using namespace std;
int g[64][64], n, m;
int used[64][64];
pair<int, int> path[64], pre[64][64];
const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};
struct Area {
    vector<pair<int, int> > V;
    bool operator<(const Area &a) const {
        for (int i = 0; i < V.size(); i++)
            if (V[i] != a.V[i]) return V[i] < a.V[i];
        return false;
    }
    Area() {
        V.clear();
    }
    Area rotate() {
        Area ret = (*this);
        for (int i = 0; i < V.size(); i++) {
            int x = ret.V[i].first, y = ret.V[i].second;
            ret.V[i].first = -y;
            ret.V[i].second = x;
        }
        return ret.normal();
    }
    Area flip() {
        Area ret = (*this);
        for (int i = 0; i < V.size(); i++) {
            int x = ret.V[i].first, y = ret.V[i].second;
            ret.V[i].first = -x;
            ret.V[i].second = y;
        }
        return ret.normal();
    }
    Area normal() {
        sort(V.begin(), V.end());
        int x, y, mx, my;
        x = V[0].first, y = V[0].second;
        mx = x, my = y;
        for (int i = 0; i < V.size(); i++) {
            x = min(x, V[i].first), y = min(y, V[i].second);
            mx = max(mx, V[i].first), my = max(my, V[i].second);
        }
        for (int i = 0; i < V.size(); i++)
            V[i].first -= x, V[i].second -= y;
        sort(V.begin(), V.end());
        return (*this);
    }
    void print() const {
        for (int i = 0; i < V.size(); i++)
            printf("(%d %d)", V[i].first, V[i].second);
        puts("");
    }
};
// Number of fixed polyominoes with n cells. https://oeis.org/A001168
set<Area> shape[16][16][16];
Area minExp(Area a) {
    Area ret = a;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 4; j++) {
            ret = min(ret, a);
            a = a.rotate();
        }
        a = a.flip();
    }
    return ret;
}
void storeArea(Area a) {
    sort(a.V.begin(), a.V.end());
    int x, y, mx, my;
    x = a.V[0].first, y = a.V[0].second;
    mx = x, my = y;
    for (int i = 0; i < a.V.size(); i++) {
        x = min(x, a.V[i].first), y = min(y, a.V[i].second);
        mx = max(mx, a.V[i].first), my = max(my, a.V[i].second);
    }
    for (int i = 0; i < a.V.size(); i++)
        a.V[i].first -= x, a.V[i].second -= y;
    sort(a.V.begin(), a.V.end());
    if (mx - x + 1 <= my - y + 1)
        shape[a.V.size()][mx - x + 1][my - y + 1].insert(a);
    assert(mx - x >= 0 && mx - x < 16 && my - y >= 0 && my - y < 16);
}
void dfs(int idx, int x, int y, int pick, int m) {
    if (pick == m) {
        Area t;
        for (int i = 0; i < pick; i++)
            t.V.push_back(path[i]);
        storeArea(t);
        return ;
    }
    if (idx >= 2 * m)
        return;
    vector< pair<int,int> > test;
    for (int i = 0; i < 4; i++) {
        int tx = x + dx[i],
        ty = y + dy[i];
        if (used[tx][ty])
            continue;
        pre[tx][ty] = make_pair(x, y);
        path[pick] = make_pair(tx, ty);
        used[tx][ty] = 1;
        dfs(idx+1, tx, ty, pick + 1, m);
        test.push_back(make_pair(tx, ty));
    }
    if (pre[x][y].first != -1) // stop on leaf
        dfs(idx+1, pre[x][y].first, pre[x][y].second, pick, m);
    for (int i = 0; i < test.size(); i++) {
        int tx = test[i].first,
        ty = test[i].second;
        used[tx][ty] = 0;
    }
}
int main() {
    for (int i = 1; i <= 10; i++) {
        for (int j = 0; j < 32; j++)
            for (int k = 0; k < 32; k++)
                pre[j][k] = make_pair(-1, -1);
        pre[11][11] = make_pair(-1, -1);
        path[0] = make_pair(11, 11);
        used[11][11] = 1;
        dfs(1, 11, 11, 1, i);
        used[11][11] = 0;
        int sum = 0;
        for (int j = 0; j < i; j++) {
            for (int k = 0; k < i; k++)
                sum += shape[i][j][k].size();
        }
    }
    int N, H, W;
    while (scanf("%d %d %d", &N, &H, &W) == 3) {
        set<Area> ret;
        if (H > W)
            swap(H, W);
        for (int i = 1; i <= H; i++) {
            for (int j = i; j <= W; j++) {
                for (set<Area>::iterator it = shape[N][i][j].begin();
                     it != shape[N][i][j].end(); it++) {
                    ret.insert(minExp(*it));
                }
            }
        }
//        for (set<Area>::iterator it = ret.begin(); it != ret.end(); it++) {
//            (*it).print();
//        }
        printf("%d\n", (int)ret.size());
    }
    return 0;
}