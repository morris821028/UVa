#include <stdio.h>
#include <algorithm>
#include <string.h>
#define maxN 20005
using namespace std;
struct ele {
    int x, y, in;
};
int x[maxN], y[maxN], R[maxN];
int C[maxN], out[maxN], lowbit[maxN], size;
ele IN[maxN], P[maxN];
bool cmp(ele a, ele b) {
    return a.x < b.x;
}
void modify(int idx) {
    while(idx <= size) {
        C[idx]++;
        idx += lowbit[idx];
    }
}
int query(int idx) {
    static int sum;
    sum = 0;
    while(idx) {
        sum += C[idx];
        idx -= lowbit[idx];
    }
    return sum;
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
int bsearch(int v, int l, int r, int *A) {
    static int m;
    while(l <= r) {
        m = (l+r)>>1;
        if(A[m] == v)
            return m+1;
        if(A[m] < v)
            l = m+1;
        else
            r = m-1;
    }
    return l;
}
int main() {
    int n, m, q, cases = 0;
    int ax, ay, bx, by, i, j;
    for(i = 1; i < 20005; i++)
        lowbit[i] = i&(-i);
    while(scanf("%d", &n) == 1 && n) {
        printf("Case %d:\n", ++cases);
        for(i = 0; i < n; i++) {
            ReadInt(&x[i]);
            ReadInt(&y[i]);
        }
        scanf("%d %d %d %d", &ax, &ay, &bx, &by);
        scanf("%d", &q);
        for(i = 0; i < q; i++) {
            ReadInt(&IN[i].x);
            ReadInt(&IN[i].y);
            IN[i].x = IN[i].x*IN[i].x;
            IN[i].y = IN[i].y*IN[i].y;
            IN[i].in = i;
        }
        for(i = 0; i < n; i++) {
            P[i].x = (x[i]-ax)*(x[i]-ax)+(y[i]-ay)*(y[i]-ay);
            P[i].y = (x[i]-bx)*(x[i]-bx)+(y[i]-by)*(y[i]-by);
            R[i] = P[i].y;
            C[i+1] = 0;
        }
        sort(IN, IN+q, cmp);
        sort(P, P+n, cmp);
        sort(R, R+n);
        for(i = 1, j = 0; i < n; i++) {
            if(R[i] != R[j])
                R[++j] = R[i];
        }
        size = j+1, m = j;
        for(i = 0, j = 0; i < q; i++) {
            while(j < n && P[j].x <= IN[i].x) {
                modify(bsearch(P[j].y, 0, m, R));
                j++;
            }
            out[IN[i].in] = query(bsearch(IN[i].y, 0, m, R));
        }
        for(i = 0; i < q; i++)
            printf("%d\n", out[i]);
    }
    return 0;
}
