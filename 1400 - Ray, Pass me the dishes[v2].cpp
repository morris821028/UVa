#include <stdio.h>
#include <algorithm>
using namespace std;
#define oo 1LL<<60
struct node {
    int l, r;
    long long v;
    bool operator<(const node &a) const {
        if(v != a.v)    return v < a.v;
        if(l != a.l)    return l > a.l;
        return r > a.r;
    }
    node(int a, int b, long long c):
        l(a), r(b), v(c) {}
    node():
        l(0), r(0), v(0) {}
};
struct STnode {
    int lmax, rmax; // by index record
    node ret;
};
STnode ST[1048576];
long long A[1048576], SUM[1048576];
void build(int k, int l, int r) {
    if(l == r) {
        ST[k].lmax = ST[k].rmax = l;
        ST[k].ret = node(l, r, A[l]);
        return ;
    }
    if(l > r) {
        ST[k].ret = node(-1, -1, -oo);
        return ;
    }
    int m = (l+r)/2;
    build(k<<1, l, m);
    build(k<<1|1, m+1, r);

    ST[k].ret = node(l, r, -oo);
    ST[k].ret = max(ST[k].ret, ST[k<<1].ret);
    ST[k].ret = max(ST[k].ret, ST[k<<1|1].ret);
    ST[k].ret = max(ST[k].ret,
            node(ST[k<<1].rmax, ST[k<<1|1].lmax, SUM[ST[k<<1|1].lmax]-SUM[ST[k<<1].rmax-1]));

    ST[k].lmax = ST[k<<1].lmax;
    if(SUM[ST[k].lmax]-SUM[l-1] < SUM[ST[k<<1|1].lmax]-SUM[l-1])
        ST[k].lmax = ST[k<<1|1].lmax;

    ST[k].rmax = ST[k<<1|1].rmax;
    if(SUM[r]-SUM[ST[k].rmax-1] <= SUM[r]-SUM[ST[k<<1].rmax-1])
        ST[k].rmax = ST[k<<1].rmax;
}
node query(int k, int l, int r, int ql, int qr, int &pl, int &pr) {
    if(ql <= l && r <= qr) {
        pl = ST[k].lmax;
        pr = ST[k].rmax;
        return ST[k].ret;
    }
    int m = (l+r)/2;
    node ans = node(l, r, -oo);
    int lpre, lsuf, rpre, rsuf;
    pl = -1, pr = -1;
    if(ql <= m && qr > m) {
        ans = max(ans, query(k<<1, l, m, ql, qr, lpre, lsuf));
        ans = max(ans, query(k<<1|1, m+1, r, ql, qr, rpre, rsuf));
        if(lsuf != -1 && rpre != -1)
            ans = max(ans, node(lsuf, rpre, SUM[rpre]-SUM[lsuf-1]));
        if(ql <= l) {
            pl = lpre;
            if(SUM[lpre]-SUM[l-1] < SUM[rpre]-SUM[l-1])
                pl = rpre;
        }
        if(qr >= r) {
            pr = rsuf;
            if(SUM[r]-SUM[rsuf-1] <= SUM[r]-SUM[lsuf-1])
                pr = lsuf;
        }
    } else if(qr <= m) {
        ans = max(ans, query(k<<1, l, m, ql, qr, lpre, lsuf));
        if(ql <= l) pl = lpre;
    } else if(ql > m){
        ans = max(ans, query(k<<1|1, m+1, r, ql, qr, rpre, rsuf));
        if(qr >= r) pr = rsuf;
    }
    return ans;
}
int main() {
    int n, q, l, r, cases = 0;
    int i, j;
    while(scanf("%d %d", &n, &q) == 2) {
        for(i = 1; i <= n; i++) {
            scanf("%lld", &A[i]);
            SUM[i] = SUM[i-1] + A[i];
        }
        build(1, 1, n);
        printf("Case %d:\n", ++cases);
        int tl, tr;
        while(q--) {
            scanf("%d %d", &l, &r);
            node ans = query(1, 1, n, l, r, tl, tr);
            printf("%d %d\n", ans.l, ans.r);
        }
    }
    return 0;
}
