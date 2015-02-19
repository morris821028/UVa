#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <queue>
#include <stack>
#include <assert.h>
#include <set>
using namespace std;
/*
 http://blog.sina.com.cn/s/blog_700906660100v7vb.html
 http://wenku.baidu.com/view/fdb484c3bb4cf7ec4afed08b.html
 */
const int MAXV = 256;
const int INF = 1<<29;

class StoerWagner {
public:
    int g[MAXV][MAXV], visited[MAXV], weight[MAXV];
    int contract[MAXV];
    void addEdge(int x, int y, int v) {
        g[x][y] += v, g[y][x] += v;
    }
    void init(int N) {
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                g[i][j] = 0;
    }
    int randomMincut(int &s, int &t, int N) {
        int ret = 0;
        s = t = -1;
        for (int i = 0; i < N; i++)
            visited[i] = weight[i] = 0;
        for (int i = 0; i < N; i++) {
            int mx = -INF, u = t;
            for (int j = 0; j < N; j++) {
                if (!contract[j] && !visited[j] && weight[j] > mx) {
                    mx = weight[j], u = j;
                }
            }
            if (u == t) break;
            s = t, t = u, ret = mx;
            visited[u] = 1;
            for (int j = 0; j < N; j++) {
                if (!contract[j] && !visited[j])
                    weight[j] += g[u][j];
            }
        }
        return ret;
    }
    int Mincut(int N) {
        for (int i = 0; i < N; i++)
            contract[i] = 0;
        int ret = INF;
        for (int i = 0; i < N-1; i++) {
            int s, t;
            int stMincut = randomMincut(s, t, N);
            ret = min(ret, stMincut);
            if (ret == 0)   return ret;
            contract[t] = 1;
            for (int j = 0; j < N; j++) { // contract(s, t)
                if (!contract[j]) {
                    g[s][j] += g[t][j];
                    g[j][s] += g[j][t];
                }
            }
        }
        return ret;
    }
} g;

int main() {
    int testcase, cases = 0;
    int N, M, x, y, v;
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d %d", &N, &M);
        g.init(N);
        for (int i = 0; i < M; i++) {
            scanf("%d %d %d", &x, &y, &v);
            x--, y--;
            g.addEdge(x, y, v);
        }
        int ret = g.Mincut(N);
        printf("Case #%d: %d\n", ++cases, ret);
    }
    return 0;
}
/*
 4
 5
 4
 1 2 100
 2 3 299
 3 5 400
 5 4 99
 3
 3
 1 2 10
 2 3 20
 1 3 40
 4
 5
 1 2 10
 2 3 100
 3 4 10
 4 1 100
 1 3 10
 3
 1
 1 2 1000
 */
