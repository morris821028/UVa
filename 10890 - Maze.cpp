#include <stdio.h>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;
int N, S, T, X[35], Y[35];
int dist[35][35];
struct STATE {
    int used, cnt, nd;
    int g, h;
    bool operator<(const STATE &e) const {
        if(h+g != e.h+e.g)
            return h+g > e.h+e.g; // min
        if(g != e.g)
            return g > e.g; // max
        if(cnt != e.cnt)
            return cnt < e.cnt; // max
        return X[nd]+Y[nd] < X[e.nd]+Y[e.nd];
    }
    STATE(int a, int b, int c, int d, int e):
        used(a), cnt(b), nd(c), g(d), h(e) {}
};
int H(STATE &v) {
    static int h1, h2, i, j;
    h1= h2 = 0xfffff;
    if(v.cnt == S)
        return N-X[v.nd]+N-Y[v.nd]-2;
    if(v.cnt == S-1) {
        for(i = 0; i < T; i++) {
            if(!((v.used>>i)&1))
                return dist[i][v.nd] + N-X[i]+N-Y[i]-2;
        }
    }
    for(i = 0; i < T; i++) {
        if(!((v.used>>i)&1)) {
            h2 = min(h2, N-X[i]+N-Y[i]-2);
            for(j = i+1; j < T; j++) {
                if(!((v.used>>j)&1)) {
                    h1 = min(h1, dist[i][j]);
                }
            }
        }
    }
    h2 = min(h2, N-X[v.nd]+N-Y[v.nd]-2);
    return h1 * (S-v.cnt) + h2;
}
void sol() {
    int i, j;
    priority_queue<STATE, vector<STATE> > pQ;
    for(i = 0; i < T; i++)
        for(j = 0; j < T; j++)
            dist[i][j] = abs(X[i]-X[j])+abs(Y[i]-Y[j]);
    STATE tn(0,0,0,0,0), tm = tn;
    for(i = 0; i < T; i++) {
        tn.used = 1<<i, tn.cnt = 1, tn.nd = i;
        tn.g = X[i]+Y[i];
        tn.h = H(tn);
        pQ.push(tn);
    }
    while(!pQ.empty()) {
        tn = pQ.top(), pQ.pop();
        //printf("%d", tn.cnt);
        //printf("%d: g %d h %d used %d\n", tn.nd, tn.g, tn.h, tn.used);
        if(tn.cnt == S) {
            printf("%d\n", tn.g+tn.h);
            return;
        }
        for(i = 0; i < T; i++) {
            if((tn.used>>i)&1)
                continue;
            tm = tn;
            tm.cnt++, tm.nd = i, tm.used |= 1<<i;
            tm.g += dist[tn.nd][i];
            tm.h = H(tm);
            pQ.push(tm);
        }
    }
}
int main() {
    int i, cases = 0;
    while(scanf("%d %d %d", &N, &T, &S) == 3) {
        if(N+S+T == 0)
            break;
        for(i = 0; i < T; i++)
            scanf("%d %d", &X[i], &Y[i]);
        printf("Case %d: ", ++cases);
        sol();
    }
    return 0;
}
/*
4 4 4
2 0
2 1
2 2
0 2
4 4 2
2 0
2 1
2 2
0 2
*/
