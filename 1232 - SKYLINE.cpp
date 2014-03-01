#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
struct Node {
    int mx, mn, label;
};
Node ST[(1<<18)+1];
long long ret;
void update(int k) {
    ST[k].mx = max(ST[k<<1].mx, ST[k<<1|1].mx);
    ST[k].mn = min(ST[k<<1].mn, ST[k<<1|1].mn);
}
void downdate(int k) {
    if(ST[k].label) {
        ST[k<<1].mx = ST[k<<1].mn = ST[k<<1].label = ST[k].label;
        ST[k<<1|1].mx = ST[k<<1|1].mn = ST[k<<1|1].label = ST[k].label;
        ST[k].label = 0;
    }
}
void modify(int k, int l, int r, int &ql, int &qr, int h) {
    if(l > r)
        return;
    if(l != r)
        downdate(k);
    if(ST[k].mn > h)
        return;
    if(ql <= l && r <= qr) {
        if(h >= ST[k].mx) {
            ret += r-l+1;
            ST[k].mx = ST[k].mn = ST[k].label = h;
            return;
        }
        // still update sub-interval
    }
    int m = (l+r)>>1;
    if(ql > m)
        modify(k<<1|1, m+1, r, ql, qr, h);
    else if(qr <= m)
        modify(k<<1, l, m, ql, qr, h);
    else {
        modify(k<<1, l, m, ql, qr, h);
        modify(k<<1|1, m+1, r, ql, qr, h);
    }
    update(k);
}
int main() {
    int testcase, n, x, y, h;
    int i, j;
    scanf("%d", &testcase);
    while(testcase--) {
        scanf("%d", &n);
        memset(ST, 0, sizeof(ST));
        ret = 0;
        for(i = 0; i < n; i++) {
            scanf("%d %d %d", &x, &y, &h);
            y--;
            modify(1, 1, 100000, x, y, h);
        }
        printf("%lld\n", ret);
    }
    return 0;
}
