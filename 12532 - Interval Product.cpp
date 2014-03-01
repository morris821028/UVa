#include <stdio.h>
int A[100000];
int ST[262144][2];
void build(int k, int l, int r) {
    ST[k][0] = ST[k][1] = 0;
    if(l == r) {
        ST[k][1] = (A[l] == 0);
        ST[k][0] = A[l] < 0;
        return ;
    }
    if(l < r) {
        int m = (l+r)/2;
        build(k<<1, l, m);
        build(k<<1|1, m+1, r);
        ST[k][0] = ST[k<<1][0]+ST[k<<1|1][0];
        ST[k][1] = ST[k<<1][1]|ST[k<<1|1][1];
    }
}
void update(int k, int l, int r, int qx, int qv) {
    if(l == r && l == qx) {
        A[l] = qv;
        ST[k][1] = (A[l] == 0);
        ST[k][0] = A[l] < 0;
        return;
    }
    int m = (l+r)/2;
    if(qx <= m)
        update(k<<1, l, m, qx, qv);
    else
        update(k<<1|1, m+1, r, qx, qv);
    ST[k][0] = ST[k<<1][0]+ST[k<<1|1][0];
    ST[k][1] = ST[k<<1][1]|ST[k<<1|1][1];
}
int neg, has;
void query(int k, int l, int r, int ql, int qr) {
    if(l == ql && r == qr) {
        neg += ST[k][0];
        has |= ST[k][1];
        return;
    }
    int m = (l+r)/2;
    if(qr <= m) {
        query(k<<1, l, m, ql, qr);
    } else if(ql > m) {
        query(k<<1|1, m+1, r, ql, qr);
    } else {
        query(k<<1, l, m, ql, m);
        query(k<<1|1, m+1, r, m+1, qr);
    }
}
int main() {
    int n, k, i, x, y;
    char cmd[2];
    while(scanf("%d %d", &n, &k) == 2) {
        for(i = 1; i <= n; i++)
            scanf("%d", &A[i]);
        build(1, 1, n);
        while(k--) {
            scanf("%s %d %d", cmd, &x, &y);
            if(cmd[0] == 'C') {
                update(1, 1, n, x, y);
            } else {
                neg = 0, has = 0;
                query(1, 1, n, x, y);
                if(has)
                    printf("0");
                else if(neg&1)
                    printf("-");
                else
                    printf("+");
            }
        }
        puts("");
    }
    return 0;
}
