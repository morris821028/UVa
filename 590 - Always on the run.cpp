#include <stdio.h>
#include <queue>
#define oo 0xfffff
using namespace std;
int g[15][15][30] = {}, gt[15][15] = {};
int dist[15][1001], used[15][1001] = {};
int i, j, k;
struct ele {
    int nd, d;
};
void spfa(int N, int K) {
    for(i = 1; i <= N; i++)
        for(j = 0; j <= K; j++)
            dist[i][j] = oo;
    queue<ele> Q;
    ele tn, tmp;
    tn.nd = 1, tn.d = 0;
    dist[1][0] = 0;
    Q.push(tn);
    while(!Q.empty()) {
        tn = Q.front();
        Q.pop();
        used[tn.nd][tn.d] = 0;
        if(tn.d == K)   continue;
        for(i = 1; i <= N; i++) {
            if(gt[tn.nd][i] == 0)
                continue;
            j = tn.d%gt[tn.nd][i];
            if(g[tn.nd][i][j] &&
               dist[tn.nd][tn.d]+g[tn.nd][i][j] < dist[i][tn.d+1]) {
                dist[i][tn.d+1] = dist[tn.nd][tn.d]+g[tn.nd][i][j];
                if(used[i][tn.d+1] == 0) {
                    tmp.nd = i, tmp.d = tn.d+1;
                    Q.push(tmp);
                    used[i][tn.d+1] = 1;
                }
            }
        }
    }
    if(dist[N][K] != oo)
        printf("The best flight costs %d.\n", dist[N][K]);
    else
        printf("No flight possible.\n");
    puts("");
}
int main() {
    int N, K, cases = 0;
    while(scanf("%d %d", &N, &K) == 2) {
        if(N == 0)  break;
        printf("Scenario #%d\n", ++cases);
        for(i = 1; i <= N; i++) {
            for(j = 1; j <= N; j++) {
                if(i == j)  continue;
                scanf("%d", &gt[i][j]);
                for(k = 0; k < gt[i][j]; k++)
                    scanf("%d", &g[i][j][k]);
            }
        }
        spfa(N, K);
    }
    return 0;
}
