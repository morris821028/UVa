#include <stdio.h>
#include <iostream>
#include <string.h>
#include <map>
#include <queue>
using namespace std;
struct edge {
    int to;
    short startTime, endTime;
    edge(int a, short b, short c):
        to(a),startTime(b),endTime(c) {}
};
vector<edge> g[105];
short dist[2400][105];
void solve(char *name1, char *name2, int st, int ed, int st_time, int n) {
    int i, j, k;
    memset(dist, -1, sizeof(dist));
    for(i = 0; i < g[st].size(); i++) {
        if(g[st][i].startTime >= st_time) {
            dist[g[st][i].endTime][g[st][i].to] =
                max(dist[g[st][i].endTime][g[st][i].to], g[st][i].startTime);
        }
    }
    for(i = st_time; i < 2400; i++) {
        for(j = 0; j < n; j++) {
            if(dist[i][j] == -1)    continue;
            for(k = 0; k < g[j].size(); k++) {
                if(g[j][k].startTime >= i) {
                    dist[g[j][k].endTime][g[j][k].to] =
                        max(dist[g[j][k].endTime][g[j][k].to], dist[i][j]);
                }
            }
        }
        if(dist[i][ed] != -1) {
            printf("Departure %04d %s\n", dist[i][ed], name1);
            printf("Arrival   %04d %s\n", i, name2);
            return;
        }
    }
    puts("No connection");
}
int main() {
    int testcase, cases = 0;
    int N, T, M;
    int i, j, k;
    scanf("%d", &testcase);
    char cityName[1024], start[1024], end[1024];
    while(testcase--) {
        scanf("%d", &N);
        map<string, int> R;
        for(i = 0; i < N; i++) {
            scanf("%s", &cityName);
            R[cityName] = i;
            g[i].clear();
        }
        scanf("%d", &T);
        int x, y, ptime, time, startTime;
        while(T--) {
            scanf("%d", &M);
            for(i = 0; i < M; i++) {
                scanf("%d %s", &time, cityName);
                y = R[cityName];
                if(i && time >= ptime) {
                    g[x].push_back(edge(y, ptime, time));
                }
                x = y, ptime = time;
            }
        }
        scanf("%d %s %s", &startTime, start, end);
        x = R[start];
        y = R[end];
        printf("Scenario %d\n", ++cases);
        solve(start, end, x, y, startTime, N);
        puts("");
    }
    return 0;
}
/*
why use dp not short path algorithm?
for example. A-> B ->C
|----------------||---------------|
   |-------------------||--------|
  |------------------||---------|
*/
