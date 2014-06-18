#include <stdio.h>
#include <vector>
#include <queue>
#define maxn 1000005
using namespace std;
vector<int> g[maxn];
int indeg[maxn], ans[maxn];
inline int readchar() {
    const int N = 1048576;
    static char buf[N];
    static char *p = buf, *end = buf;
    if(p == end) {
        if((end = buf + fread(buf, 1, N, stdin)) == buf) return EOF;
        p = buf;
    }
    return *p++;
}
inline int ReadInt(int *x) {
    static char c, neg;
    while((c = readchar()) < '-')    {if(c == EOF) return 0;}
    neg = (c == '-') ? -1 : 1;
    *x = (neg == 1) ? c-'0' : 0;
    while((c = readchar()) >= '0')
        *x = (*x << 3) + (*x << 1) + c-'0';
    *x *= neg;
    return 1;
}
int main() {
    int n, m, i, x, y, tn;
    while(ReadInt(&n)) {
        if(n == 0)  break;
        ReadInt(&m);
        for(i = 1; i <= n; i++)
            g[i].clear(), indeg[i] = 0;
        while(m--) {
            ReadInt(&x);
            ReadInt(&y);
            g[x].push_back(y);
            indeg[y]++;
        }
        queue<int> Q;
        for(i = 1; i <= n; i++)
            if(indeg[i] == 0)
                Q.push(i);
        int at = 0;
        while(!Q.empty()) {
            tn = Q.front(), Q.pop();
            ans[at++] = tn;
            for(vector<int>::iterator it = g[tn].begin();
                it != g[tn].end(); it++) {
                if(--indeg[*it] == 0) {
                    Q.push(*it);
                }
            }
        }
        if(at != n) puts("IMPOSSIBLE");
        else    for(i = 0; i < n; i++)
            printf("%d\n", ans[i]);
    }
    return 0;
}
