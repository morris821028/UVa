#include <stdio.h>
#include <string.h>
#define max(x, y) ((x) > (y) ? (x) : (y))
#define min(x, y) ((x) < (y) ? (x) : (y))
struct subTree {
    int l, r;
    int maxv, minv;
};
struct segmentTree {
    int l, r;
    subTree subtree[1025];
} mainTree[1025];
void subbuild(int fk, int nk, int l, int r) {
    mainTree[fk].subtree[nk].l = l;
    mainTree[fk].subtree[nk].r = r;
    if(l >= r)
        return;
    int m = (l+r)>>1;
    subbuild(fk, nk<<1, l, m);
    subbuild(fk, nk<<1|1, m+1, r);
}
void build(int k, int lr, int rr, int lc, int rc) {
    mainTree[k].l = lr;
    mainTree[k].r = rr;
    subbuild(k, 1, lc, rc);
    if(lr >= rr)
        return;
    int m = (lr+rr)>>1;
    build(k<<1, lr, m, lc, rc);
    build(k<<1|1, m+1, rr, lc, rc);
}
void submodify(int fk, int nk, int x, int y, int v) {
    if(mainTree[fk].subtree[nk].l == y && mainTree[fk].subtree[nk].r == y) {
        if(mainTree[fk].l == x && mainTree[fk].r == x) {
            mainTree[fk].subtree[nk].maxv = v;
            mainTree[fk].subtree[nk].minv = v;
        } else {
            mainTree[fk].subtree[nk].maxv = max(mainTree[fk<<1].subtree[nk].maxv, mainTree[fk<<1|1].subtree[nk].maxv);
            mainTree[fk].subtree[nk].minv = min(mainTree[fk<<1].subtree[nk].minv, mainTree[fk<<1|1].subtree[nk].minv);
        }
    }
    if(mainTree[fk].subtree[nk].l >= mainTree[fk].subtree[nk].r)
        return;
    int m = (mainTree[fk].subtree[nk].l+mainTree[fk].subtree[nk].r)>>1;
    if(y <= m)
        submodify(fk, nk<<1, x, y, v);
    else
        submodify(fk, (nk<<1)+1, x, y, v);
    if(mainTree[fk].l != mainTree[fk].r) {
        mainTree[fk].subtree[nk].maxv = max(mainTree[fk<<1].subtree[nk].maxv, mainTree[fk<<1|1].subtree[nk].maxv);
        mainTree[fk].subtree[nk].minv = min(mainTree[fk<<1].subtree[nk].minv, mainTree[fk<<1|1].subtree[nk].minv);
    } else {
        mainTree[fk].subtree[nk].maxv = max(mainTree[fk].subtree[nk<<1].maxv, mainTree[fk].subtree[nk<<1|1].maxv);
        mainTree[fk].subtree[nk].minv = min(mainTree[fk].subtree[nk<<1].minv, mainTree[fk].subtree[nk<<1|1].minv);
    }
}
void modify(int k, int x, int y, int v) {
    if(mainTree[k].l == x && mainTree[k].r == x) {
        submodify(k, 1, x, y, v);
    }
    if(mainTree[k].l >= mainTree[k].r)
        return;
    int m = (mainTree[k].l+mainTree[k].r)>>1;
    if(x <= m)
        modify(k<<1, x, y, v);
    else
        modify(k<<1|1, x, y, v);
    submodify(k, 1, x, y, v);
}
int ansMax, ansMin;
void subquery(int fk, int nk, int lc, int rc) {
    if(mainTree[fk].subtree[nk].l == lc && mainTree[fk].subtree[nk].r == rc) {
        ansMax = max(ansMax, mainTree[fk].subtree[nk].maxv);
        ansMin = min(ansMin, mainTree[fk].subtree[nk].minv);
        return;
    }
    if(mainTree[fk].subtree[nk].l >= mainTree[fk].subtree[nk].r)
        return;
    int m = (mainTree[fk].subtree[nk].l+mainTree[fk].subtree[nk].r)>>1;
    if(rc <= m)
        subquery(fk, nk<<1, lc, rc);
    else if(lc > m)
        subquery(fk, nk<<1|1, lc, rc);
    else {
        subquery(fk, nk<<1, lc, m);
        subquery(fk, nk<<1|1, m+1, rc);
    }

}
void query(int k, int lr, int rr, int lc, int rc) {
    if(mainTree[k].l == lr && mainTree[k].r == rr) {
        subquery(k, 1, lc, rc);
        return;
    }
    if(mainTree[k].l >= mainTree[k].r)
        return;
    int m = (mainTree[k].l+mainTree[k].r)>>1;
    if(rr <= m)
        query(k<<1, lr, rr, lc, rc);
    else if(lr > m)
        query(k<<1|1, lr, rr, lc, rc);
    else {
        query(k<<1, lr, m, lc, rc);
        query(k<<1|1, m+1, rr,lc, rc);
    }
}
int main() {
    int n, m, q, x, y, v;
    int i, j, x1, x2, y1, y2;
    while(scanf("%d %d", &n, &m) == 2) {
        build(1, 1, n, 1, m);
        for(i = 1; i <= n; i++) {
            for(j = 1; j <= m; j++) {
                scanf("%d", &x);
                modify(1, i, j, x);
            }
        }
        scanf("%d", &q);
        char cmd[3];
        while(q--) {
            scanf("%s", cmd);
            if(cmd[0] == 'q') {
                scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
                ansMax = 0, ansMin = 0xfffffff;
                query(1, x1, x2, y1, y2);
                printf("%d %d\n", ansMax, ansMin);
            } else {
                scanf("%d %d %d %d", &x, &y, &v);
                modify(1, x, y, v);
            }
        }
    }
    return 0;
}
