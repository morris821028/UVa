#include <stdio.h>
#include <vector>
#define maxN 32768
using namespace std;
typedef struct {
    int q, i;
} Qi;
vector<int> g[maxN];
vector<Qi> qu[maxN];
int r[maxN], p[maxN], dp[maxN], used[maxN];
int oput[500000][2];
int findp(int x) {
    return p[x] == x ? x : p[x]=findp(p[x]);
}
void joint(int x, int y) {
    x = findp(x), y = findp(y);
    p[x] = y;
}
void dfs(int nd, int dep) {
    dp[nd] = dep, used[nd] = 1;
    for(vector<Qi>::iterator it = qu[nd].begin();
        it != qu[nd].end(); it++) {
        if(used[it->q]) {
            oput[it->i][0] = findp(it->q);
            oput[it->i][1] = dp[nd]+dp[it->q]-2*dp[findp(it->q)];
        }
    }
    for(vector<int>::iterator it = g[nd].begin();
        it != g[nd].end(); it++) {
        dfs(*it, dep+1);
        joint(*it, nd);
    }
}
int ReadInt(int *x) {
    static char c, neg;
    while((c = getchar()) < '-')    {if(c == EOF) return EOF;}
    neg = (c == '-') ? -1 : 1;
    *x = (neg == 1) ? c-'0' : 0;
    while((c = getchar()) >= '0')
        *x = (*x << 3) + (*x << 1) + c-'0';
    *x *= neg;
    return 1;
}
int main() {
    int n, q, x, y, i, j;
    while(scanf("%d %d", &n, &q) == 2) {
        for(i = 1; i <= n; i++) {
            g[i].clear(), r[i] = 1, p[i] = i, used[i] = 0;
            while(ReadInt(&x), x)
                g[i].push_back(x);
        }
        Qi tmp;
        for(i = 0; i < q; i++) {
            ReadInt(&x), ReadInt(&y);
            tmp.i = i, tmp.q = y;
            qu[x].push_back(tmp);
            tmp.q = x;
            qu[y].push_back(tmp);
        }
        dfs(1, 0);
        for(i = 0; i < q; i++)
            printf("%d %d\n", oput[i][0], oput[i][1]);
    }
    return 0;
}
