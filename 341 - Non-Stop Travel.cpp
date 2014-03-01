#include <stdio.h>
#include <string.h>
#include <queue>
#define min(x, y) ((x) < (y) ? (x) : (y))
using namespace std;

int map[20][20], test = 0;
void spfa(int st, int ed, int n) {

    int dis[20], used[20], pre[20], tn, i;
    memset(dis, 63, sizeof(dis));
    memset(used, 0, sizeof(used));
    queue<int> Q;
    Q.push(ed);
    dis[ed] = 0;
    while(!Q.empty()) {
        tn = Q.front();
        Q.pop();
        used[tn] = 0;
        for(i = 1; i <= n; i++) {
            if(dis[i] > dis[tn]+map[tn][i]) {
                dis[i] = dis[tn]+map[tn][i];
                pre[i] = tn;
                if(used[i] == 0) {
                    used[i] = 1;
                    Q.push(i);
                }
            }
        }
    }
    printf("Case %d: Path =", ++test);
    i = st;
    do {
        printf(" %d", i);
        i = pre[i];
    } while(i != ed);
    printf(" %d; %d second delay\n", ed, dis[st]);
}
int main() {
    int st, ed, n;
    while(scanf("%d", &n) == 1 && n) {
        memset(map, 63, sizeof(map));
        int i, m, y, v;
        for(i = 1; i <= n; i++) {
            scanf("%d", &m);
            while(m--) {
                scanf("%d %d", &y, &v);
                map[y][i] = min(map[y][i], v);
            }
        }
        scanf("%d %d", &st, &ed);
        spfa(st, ed, n);
    }
    return 0;
}
