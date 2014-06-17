#include <stdio.h>
#include <stdlib.h>
typedef struct {
    int x, y, v;
} ele;
ele D[1000005];
int cmp(const void *i, const void *j) {
    ele *a, *b;
    a = (ele *)i, b = (ele *)j;
    return a->v - b->v;
}
struct {
    int subtree[2050];
} mainTree[2050];
int Mmain, Msub;
void subbuild(int k) {
    int i;
    for(i = 2*Msub-1; i > 0; i--)
        mainTree[k].subtree[i] = 0;
}
void build() {
    int i;
    for(i = 2*Mmain; i > 0; i--)
        subbuild(i);
}
void modify(int x, int y, int v) {
    mainTree[x+Mmain].subtree[y+Msub] += v;
    static int s, t;
    for(t = (x+Mmain); t > 0; t >>= 1) {
        for(s = (y+Msub)>>1; s > 0; s >>= 1) {
            mainTree[t].subtree[s] = mainTree[t].subtree[s<<1] +
                    mainTree[t].subtree[s<<1|1];
        }
    }
}
int subquery(int k, int lc, int rc) {
    static int s, t, sum;
    sum = 0;
    for(s = lc+Msub-1, t = rc+Msub+1; (s^t) != 1;) {
        if(~s&1)
            sum += mainTree[k].subtree[s^1];
        if(t&1)
            sum += mainTree[k].subtree[t^1];
        s >>= 1, t >>= 1;
    }
    return sum;
}
int query(int lr, int rr, int lc, int rc) {
    static int s, t, sum;
    sum = 0;
    for(s = lr+Mmain-1, t = rr+Mmain+1; (s^t) != 1;) {
        if(~s&1)
            sum += subquery(s^1, lc, rc);
        if(t&1)
            sum += subquery(t^1, lc, rc);
        s >>= 1, t >>= 1;
    }
    return sum;
}
int main() {
    int t, R, C, i, j, v;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &R, &C);
        int m = 0;
        for(i = 0; i < R; i++) {
            for(j = 0; j < C; j++) {
                scanf("%d", &v);
                D[m].x = i, D[m].y = j, D[m].v = v;
                m++;
            }
        }
        qsort(D, m, sizeof(ele), cmp);
        for(Mmain = 1; Mmain < R+2; Mmain <<= 1);
        for(Msub = 1; Msub < C+2; Msub <<= 1);
        build();
        for(i = 0; i < m; i++) {
            int tmp = query(1, D[i].x+1, 1, D[i].y+1);
            tmp++;
            modify(D[i].x+1, D[i].y+1, tmp);
        }
        printf("%d\n", query(1, R, 1, C));
    }
    return 0;
}
