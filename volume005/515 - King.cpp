#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;
struct arc {
    int to, w;
};
arc g[105][105];
int gt[105], inq[105], dis[105];
int used[105];
int neg_spfa(int n) {
    static int i, j, tn, to, w;
    queue<int> Q;
    for(i = 0; i <= n; i++) {
        dis[i] = 0, used[i] = 1, inq[i] = 0;
        Q.push(i);
    }
    while(!Q.empty()) {
        tn = Q.front();
        Q.pop();
        used[tn] = 0;
        for(j = gt[tn]-1; j >= 0; j--) {
            to = g[tn][j].to, w = g[tn][j].w;
            if(dis[to] > dis[tn] + w) {
                dis[to] = dis[tn] + w;
                if(!used[to]) {
                    used[to] = 1;
                    Q.push(to);
                    if(++inq[to] > n)
                        return 1;
                }
            }
        }
    }
    return 0;
}
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
    int n, m, i, j, w;
    char cmd[5];
    while(ReadInt(&n)) {
        if(n == 0)  break;
        ReadInt(&m);
        for(i = 0; i <= n; i++)
            gt[i] = 0;
        while(m--) {
            ReadInt(&i), ReadInt(&j);
            cmd[0] = readchar(), cmd[1] = readchar();
            ReadInt(&w);
            //scanf("%d %d %s %d", &i, &j, cmd, &w);
            j += i, i--;  // S(j) - S(i-1)
            if(cmd[0] == 'l') {// < w
                w--; // <= w
                g[i][gt[i]].to = j;
                g[i][gt[i]++].w = w;
            } else { // > w
                w++; // >= w
                g[j][gt[j]].to = i;
                g[j][gt[j]++].w = -w;
            }
        }
        if(neg_spfa(n))
            puts("successful conspiracy");
        else
            puts("lamentable kingdom");
    }
    return 0;
}
