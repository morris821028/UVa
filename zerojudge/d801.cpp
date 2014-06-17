#include <stdio.h>
#include <algorithm>
#define INF 200000000
using namespace std;
struct ND {
    int mx, mn;
} ST[1<<21|1];
int M, ST2[1<<21|1];

void setST(int n) {
    int i;
    for(i = 2*M-1; i > 0; i--) {
        ST[i].mx = -INF;
        ST[i].mn = INF;
        if(i >= M)
            ST2[i] = 1;
        else
            ST2[i] = ST2[i<<1]+ST2[i<<1|1];
    }
}
void modify(int x, int nv, int xv) {
    ST[x+M].mx = xv;
    ST[x+M].mn = nv;
    x = x+M;
    for(x >>= 1; x > 0; x >>= 1) {
        ST[x].mn = min(ST[x<<1].mn, ST[x<<1|1].mn);
        ST[x].mx = max(ST[x<<1].mx, ST[x<<1|1].mx);
    }
}
void query(int& s, int& t) {
    static int i;
    static ND ans;
    ans.mn = INF, ans.mx = -INF;
    for(s = s+M-1, t = t+M+1; (s^t) != 1;) {
        if(~s&1) {
            ans.mn = min(ans.mn, ST[s^1].mn);
            ans.mx = max(ans.mx, ST[s^1].mx);
        }
        if(t&1) {
            ans.mn = min(ans.mn, ST[t^1].mn);
            ans.mx = max(ans.mx, ST[t^1].mx);
        }
        s >>= 1, t >>= 1;
    }
    printf("%d %d\n", ans.mn, ans.mx);
}
int getIdx(int idx) {
    static int s;
    for(s = 1; s < M;) {
        if(ST2[s<<1] < idx)
            idx -= ST2[s<<1], s = s<<1|1;
        else
            s = s<<1;
    }
    return s-M+1;
}
void delIdx(int idx) {
    idx = idx+M-1;
    while(idx)
        ST2[idx]--, idx >>= 1;
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
    int n, m, i, j, sum;
    int I, J, c, A;
    while(scanf("%d %d", &n, &m) == 2) {
        for(M = 1; M < n+2; M <<= 1);
        setST(n);
        for(i = 1; i <= n; i++) {
            ReadInt(&A);
            modify(i, A, A);
        }
        while(m--) {
            ReadInt(&c);
            ReadInt(&I);
            if(c == 1) {
                I = getIdx(I);
                modify(I, INF, -INF);
                delIdx(I);
            } else {
                ReadInt(&J);
                I = getIdx(I);
                J = getIdx(J);
                query(I, J);
            }
        }
    }
    return 0;
}
