#include <stdio.h>
#include <string.h>
#define max(x, y) ((x) > (y) ? (x) : (y))
#define min(x, y) ((x) < (y) ? (x) : (y))
struct subTree {
    int maxv;
};
struct segmentTree {
    subTree subtree[1025];
} mainTree[1025];
int Mmain, Msub;
void subbuild(int k) {
    int i;
    for(i = 2*Msub-1; i > 0; i--) {
        mainTree[k].subtree[i].maxv = 0;
    }
}
void build() {
    int i;
    for(i = 2*Mmain; i > 0; i--) {
        subbuild(i);
    }
}
void submodify(int k, int y) {
    static int s;
    for(s = y+Msub; s > 0; s >>= 1) {
        mainTree[k].subtree[s].maxv = max(mainTree[k<<1].subtree[s].maxv, mainTree[k<<1|1].subtree[s].maxv);
    }
}
void modify(int x, int y, int v) {
    static int s, t;
    mainTree[x+Mmain].subtree[y+Msub].maxv = v;
    t = x+Mmain;
    for(s = (y+Msub)>>1; s > 0; s >>= 1) {
        mainTree[t].subtree[s].maxv = max(mainTree[t].subtree[s<<1].maxv, mainTree[t].subtree[s<<1|1].maxv);
    }
    for(s = (x+Mmain)>>1; s > 0; s >>= 1) {
        submodify(s, y);
    }
}
int ansMax;
void subquery(int k, int lc, int rc) {
    static int s, t;
    for(s = lc+Msub-1, t = rc+Msub+1; (s^t) != 1;) {
        if(~s&1) {
            ansMax = max(ansMax, mainTree[k].subtree[s^1].maxv);
        }
        if(t&1) {
            ansMax = max(ansMax, mainTree[k].subtree[t^1].maxv);
        }
        s >>= 1, t >>= 1;
    }
}
void query(int lr, int rr, int lc, int rc) {
    static int s, t;
    for(s = lr+Mmain-1, t = rr+Mmain+1; (s^t) != 1;) {
        if(~s&1) {
            subquery(s^1, lc, rc);
        }
        if(t&1) {
            subquery(t^1, lc, rc);
        }
        s >>= 1, t >>= 1;
    }
}
inline int ReadInt(int *x) {
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
    int n, m, q, x, y, v;
    int i, j, x1, x2, y1, y2;
    while(scanf("%d %d", &n, &m) == 2) {
        for(Mmain = 1; Mmain < n+2; Mmain <<= 1);
        for(Msub = 1; Msub < m+2; Msub <<= 1);
        build();
        for(i = 1; i <= n; i++) {
            for(j = 1; j <= m; j++) {
                ReadInt(&x);
                modify(i, j, x);
            }
        }
        scanf("%d", &q);
        getchar();
        char cmd;
        while(q--) {
            ReadInt(&x1), ReadInt(&y1), ReadInt(&x2), ReadInt(&y2);
            ansMax = 0;
            query(x1, x2, y1, y2);
            printf("%d\n", ansMax);
        }
    }
    return 0;
}
