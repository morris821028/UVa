#include <stdio.h>
#include <queue>
#define oo 0xffffff
using namespace std;
int fire[505];
int g[505][505][2], gt[505];
int dist[505], f, n;
void spfa(int nd) {
    int i, j, tn, mn;
    char used[505] = {};
    queue<int> Q;
    for(i = 0; i <= n; i++)
        used[i] = 0;
    dist[nd] = 0;
    Q.push(nd);
    while(!Q.empty()) {
        tn = Q.front();
        Q.pop();
        used[tn] = 0;
        for(j = 0; j < gt[tn]; j++) {
            if(dist[g[tn][j][0]] > dist[tn]+g[tn][j][1]) {
                dist[g[tn][j][0]] = dist[tn]+g[tn][j][1];
                if(!used[g[tn][j][0]])
                    Q.push(g[tn][j][0]), used[g[tn][j][0]] = 1;
            }
        }
    }
}
int main() {
    int t, i, j;
    int a, b, c;
    char in[505];
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &f, &n);
        for(i = 0; i < f; i++)
            scanf("%d", &fire[i]);
        for(i = 0; i <= n; i++)
            gt[i] = 0, dist[i] = oo;
        gets(in);
        while(gets(in)) {
            if(!in[0])  break;
            sscanf(in, "%d %d %d", &a, &b, &c);
            g[a][gt[a]][0] = b, g[a][gt[a]++][1] = c;
            g[b][gt[b]][0] = a, g[b][gt[b]++][1] = c;
        }
        for(i = 0; i < f; i++)
            spfa(fire[i]);
        int o[505];
        for(i = 1; i <= n; i++)
            o[i] = dist[i];
        int ans = oo, anum;
        for(i = 1; i <= n; i++) {
            spfa(i);
            int mx = -oo;
            for(j = 1; j <= n; j++) {
                if(mx < dist[j])
                    mx = dist[j];
            }
            if(ans > mx)    ans = mx, anum = i;
            for(j = 1; j <= n; j++)
                dist[j] = o[j];
        }
        printf("%d\n", anum);
        if(t)   puts("");
    }
    return 0;
}
