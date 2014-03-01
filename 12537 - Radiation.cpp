#include <stdio.h>
#include <algorithm>
using namespace std;
int x[200005], y[200005];
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
int bsearch(int v, int l, int r, int *A) {
    static int m;
    while(l <= r) {
        m = (l+r)>>1;
        if(A[m] <= v)
            l = m+1;
        else
            r = m-1;
    }
    while(r >= 0 && A[r] > v) r--;
    return r+1;
}
int main() {
    int n, q, cases = 0;
    int ax, ay, bx, by, i, j, txx, tyy;
    while(scanf("%d", &n) == 1 && n) {
        printf("Case %d:\n", ++cases);
        for(i = 0; i < n; i++) {
            ReadInt(&x[i]);
            ReadInt(&y[i]);
        }
        scanf("%d %d %d %d", &ax, &ay, &bx, &by);
        scanf("%d", &q);
        for(i = 0; i < n; i++) {
            txx = (x[i]-ax)*(x[i]-ax)+(y[i]-ay)*(y[i]-ay);
            tyy = (x[i]-bx)*(x[i]-bx)+(y[i]-by)*(y[i]-by);
            x[i] = txx;
            y[i] = tyy;
        }
        sort(x, x+n);
        sort(y, y+n);
        int r1, r2, ca, cb;
        for(i = 0; i < q; i++) {
            ReadInt(&r1);
            ReadInt(&r2);
            ca = bsearch(r1*r1, 0, n-1, x);
            cb = bsearch(r2*r2, 0, n-1, y);
            r1 = n-ca-cb;
            printf("%d\n", r1 < 0 ? 0 : r1);
        }
    }
    return 0;
}
