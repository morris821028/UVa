#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
short ST[20][100010];
int AST[20][100010];
void build(int dep, int l, int r) {
    if(l < r) {
        int m = (l+r)/2, i;
        memcpy(ST[dep+1]+l, ST[dep]+l, (r-l+1)*2);
        build(dep+1, l, m);
        build(dep+1, m+1, r);
        int idx1 = l, idx2 = m+1, top = l, tmp = 0;
        while(idx1 <= m && idx2 <= r) {
            if(ST[dep+1][idx1] < ST[dep+1][idx2])
                ST[dep][top] = ST[dep+1][idx1++];
            else
                ST[dep][top] = ST[dep+1][idx2++];
            tmp += ST[dep][top];
            AST[dep][top++] = tmp;
        }
        while(idx1 <= m) {
            ST[dep][top] = ST[dep+1][idx1++];
            tmp += ST[dep][top];
            AST[dep][top++] = tmp;
        }
        while(idx2 <= r) {
            ST[dep][top] = ST[dep+1][idx2++];
            tmp += ST[dep][top];
            AST[dep][top++] = tmp;
        }
    }
    if(l == r)
        AST[dep][l] = ST[dep][l];
}
int L, R, S;
int key, Count, cost, same;
void query(int dep, int l, int r, int ql, int qr) {
    if(cost > S)   return ;
    if(l == ql && r == qr) {
        int ff = upper_bound(ST[dep]+l, ST[dep]+r+1, key)-(ST[dep]+l);
        int gg = lower_bound(ST[dep]+l, ST[dep]+r+1, key)-(ST[dep]+l);
        same += ff-gg;
        if(gg) {
            Count += gg;
            cost += AST[dep][gg+l-1];
        }
        return;
    }
    int m = (l+r)/2;
    if(m >= qr)
        query(dep+1, l, m, ql, qr);
    else if(m < ql)
        query(dep+1, m+1, r, ql, qr);
    else {
        query(dep+1, l, m, ql, m);
        query(dep+1, m+1, r, m+1, qr);
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
    int t;
    int n, q, i, j;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &n, &q);
        for(i = 1; i <= n; i++) {
            //scanf("%d", &ST[0][i]);
            ReadInt(&j);
            ST[0][i] = j;
        }
        build(0, 1, n);
        int ans = 0;
        ST[0][0] = 0;
        for(i = 1; i <= q; i++) {
            //scanf("%d %d %d", &L, &R, &S);
            ReadInt(&L);
            ReadInt(&R);
            ReadInt(&S);
            int l = 0, r = n, m;
            int x = 0;
            while(l <= r) {
                m = (l+r)/2;
                key = ST[0][m], Count = 0, cost = 0, same = 0;
                query(0, 1, n, L, R);
                if(cost <= S) {
                    l = m+1;
                    if(key)
                        Count += min((S-cost)/key, same);
                    if(Count > x)   x = Count;
                } else
                    r = m-1;
            }
            ans ^= x+i;
        }
        printf("%d\n", ans);
    }
    return 0;
}
