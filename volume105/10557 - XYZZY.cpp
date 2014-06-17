#include <stdio.h>
#include <string.h>
#include <queue>
using namespace std;
int map[101][101], mt[101];
int cap[101], arrive[101][101];
void bfs(int n, int st) {
    if(arrive[st][n] == 1)
        return;
    arrive[st][n] = 1;
    int i;
    for(i = 0; i < mt[n]; i++)
        bfs(map[n][i], st);
}
void spfa(int n) {
    if(arrive[1][n] == 0) {
        puts("hopeless");
        return;
    }
    int tn, i, j;
    int dis[101] = {}, used[101] = {};
    int update[101] = {};
    queue<int> Q;
    memset(dis, -1, sizeof(dis));
    dis[1] = 100;
    Q.push(1);
    while(!Q.empty()) {
        tn = Q.front();
        Q.pop();
        used[tn] = 0;
        update[tn]++;
        if(dis[tn] >= 0xfffffff)
            continue;
        if(update[tn] > n) {
            if(arrive[tn][n]) {
                puts("winnable");
                return;
            }
            dis[tn] = 0xfffffff;
        }
        for(i = 0; i < mt[tn]; i++) {
            if(dis[map[tn][i]] < dis[tn] + cap[map[tn][i]]) {
                dis[map[tn][i]] = dis[tn] + cap[map[tn][i]];
                if(used[map[tn][i]] == 0) {
                    used[map[tn][i]] = 1;
                    Q.push(map[tn][i]);
                }
            }
        }
    }
    if(dis[n] > 0)
        puts("winnable");
    else
        puts("hopeless");
}
int main() {
    int n, m, i, y;
    while(scanf("%d", &n) && n > 0) {
        memset(mt, 0, sizeof(mt));
        memset(arrive, 0, sizeof(arrive));
        for(i = 1; i <= n; i++) {
            scanf("%d %d", &cap[i], &m);
            while(m--) {
                scanf("%d", &y);
                map[i][mt[i]++] = y;
            }
        }
        for(i = 1; i <= n; i++)
            bfs(i, i);
        spfa(n);
    }
    return 0;
}
