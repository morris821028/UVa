#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <queue>
using namespace std;
struct Node {
    int x, y, v;// x->y, v
    int next;
} edge[20005];
int e, head[105], dis[105], prev[105], record[105];
void addEdge(int x, int y, int v) {
    edge[e].x = x, edge[e].y = y, edge[e].v = v;
    edge[e].next = head[x], head[x] = e++;
    edge[e].x = y, edge[e].y = x, edge[e].v = 0;
    edge[e].next = head[y], head[y] = e++;
}
int maxflow(int s, int t) {
    int flow = 0;
    int i, j, x, y;
    while(1) {
        memset(dis, 0, sizeof(dis));
        dis[s] =  0xffff; // oo
        queue<int> Q;
        Q.push(s);
        while(!Q.empty()) {
            x = Q.front();
            Q.pop();
            for(i = head[x]; i != -1; i = edge[i].next) {
                y = edge[i].y;
                if(dis[y] == 0 && edge[i].v > 0) {
                    prev[y] = x, record[y] = i;
                    dis[y] = min(dis[x], edge[i].v);
                    Q.push(y);
                }
            }
            if(dis[t])  break;
        }
        if(dis[t] == 0) break;
        flow += dis[t];
        for(x = t; x != s; x = prev[x]) {
            int ri = record[x];
            edge[ri].v -= dis[t];
            edge[ri^1].v += dis[t];
        }
    }
    return flow;
}
struct arc {
    int x, y, v;
    bool operator<(const arc& a) const {
        return v < a.v;
    }
};
int main() {
    int testcase;
    int N, K;
    int i, j, k;
    char s[50];
    arc D[10005];
    int A[10005], Aidx;
    scanf("%d", &testcase);
    while(testcase--) {
        scanf("%d %d", &N, &K);
        int X[105][2], Y[105][2];
        int nx = 0, ny = 0;
        for(i = 0; i < N; i++) {
            int x, y;
            scanf("%d %d %s", &x, &y, s);
            if(!strcmp(s, "blue")) {
                X[nx][0] = x;
                X[nx][1] = y;
                nx++;
            } else {
                Y[ny][0] = x;
                Y[ny][1] = y;
                ny++;
            }
        }
        int n = 0;
        for(i = 0; i < nx; i++) {
            for(j = 0; j < ny; j++) {
                D[n].x = i+1, D[n].y = nx+j+1;
                D[n].v = (X[i][0]-Y[j][0])*(X[i][0]-Y[j][0])+(X[i][1]-Y[j][1])*(X[i][1]-Y[j][1]);
                n++;
            }
        }
        sort(D, D+n);
        int l = 0, r = 3000, mid;
        int ret = 0xfffffff;
        while(l < r) {
            mid = (l+r)/2;
            e = 0;
            memset(head, -1, sizeof(head));
            for(i = 0; i < n && D[i].v <= mid*mid; i++)
                addEdge(D[i].x, D[i].y, 1);
            for(i = 0; i < nx; i++)
                addEdge(0, i+1, 1);
            for(i = 0; i < ny; i++)
                addEdge(nx+i+1, nx+ny+1, 1);
            int flow = maxflow(0, nx+ny+1);
            if(flow >= K)
                r = mid, ret = min(ret, mid);
            else
                l = mid+1;
        }
        if(ret != 0xfffffff)
            printf("%d\n", ret);
        else
            puts("Impossible");
    }
    return 0;
}
/*
2
6 2
-3 5 blue
-3 3 red
1 5 blue
2 0 red
4 6 blue
4 -1 red
*/
