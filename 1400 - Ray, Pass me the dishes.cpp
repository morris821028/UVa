#include<stdio.h>
#define N 1048576
#define Maxv 1000000000
long long A[N], Ans, f0, f1;
int B[N], st, ed, st0, ed0, st1, ed1;
struct segment {
    int l, r, m;
    int lc, rc;
    int lst, led, rst, red, mst, med;
    long long sum, lmax, rmax, midmax;
}ST[2*N + 2];
int max(int x, int y) {
    return x >= y ? x : y;
}
void init(int l, int r, int k) {
    ST[k].l = l, ST[k].r = r, ST[k].m = (l + r)>>1;
    if(l == r)  {
        ST[k].sum = ST[k].lmax = ST[k].rmax = ST[k].midmax = A[l];
        ST[k].lst = ST[k].led = ST[k].rst = ST[k].red = ST[k].mst = ST[k].med = l;
        return ;
    }
    ST[k].lc = k<<1, ST[k].rc = (k<<1)+1;
    init(l, ST[k].m, ST[k].lc), init(ST[k].m+1, r, ST[k].rc);
    ST[k].sum = ST[ST[k].lc].sum + ST[ST[k].rc].sum;

    ST[k].lmax = max(ST[ST[k].lc].lmax, ST[ST[k].lc].sum + ST[ST[k].rc].lmax);
    ST[k].lst = Maxv, ST[k].led = Maxv;
    if(ST[ST[k].lc].lmax == ST[k].lmax)
        ST[k].lst = ST[ST[k].lc].lst, ST[k].led = ST[ST[k].lc].led;
    if(ST[ST[k].lc].sum + ST[ST[k].rc].lmax == ST[k].lmax && (ST[k].lst > ST[ST[k].lc].l || (ST[k].lst == ST[ST[k].lc].l && ST[k].led > ST[ST[k].rc].led)))
        ST[k].lst = ST[ST[k].lc].l, ST[k].led = ST[ST[k].rc].led;

    ST[k].rmax = max(ST[ST[k].rc].rmax, ST[ST[k].rc].sum + ST[ST[k].lc].rmax);
    ST[k].rst = Maxv, ST[k].red = Maxv;
    if(ST[ST[k].rc].rmax == ST[k].rmax)
        ST[k].rst = ST[ST[k].rc].rst, ST[k].red = ST[ST[k].rc].red;
    if(ST[ST[k].rc].sum + ST[ST[k].lc].rmax == ST[k].rmax && (ST[k].rst > ST[ST[k].lc].rst || (ST[k].rst == ST[ST[k].lc].rst && ST[k].red > ST[ST[k].rc].r)))
        ST[k].rst = ST[ST[k].lc].rst, ST[k].red = ST[ST[k].rc].r;
    ST[k].midmax = max(max(ST[ST[k].lc].midmax, ST[ST[k].rc].midmax), ST[ST[k].lc].rmax + ST[ST[k].rc].lmax);

    ST[k].mst = Maxv, ST[k].med = Maxv;
    if(ST[ST[k].lc].midmax == ST[k].midmax)
        ST[k].mst = ST[ST[k].lc].mst, ST[k].med = ST[ST[k].lc].med;
    if(ST[ST[k].rc].midmax == ST[k].midmax && (ST[k].mst > ST[ST[k].rc].mst || (ST[k].mst == ST[ST[k].rc].mst && ST[k].med > ST[ST[k].rc].med)))
        ST[k].mst = ST[ST[k].rc].mst, ST[k].med = ST[ST[k].rc].med;
    if(ST[ST[k].lc].rmax + ST[ST[k].rc].lmax == ST[k].midmax && (ST[k].mst > ST[ST[k].lc].rst || (ST[k].mst == ST[ST[k].lc].rst && ST[k].med > ST[ST[k].rc].led)))
        ST[k].mst = ST[ST[k].lc].rst, ST[k].med = ST[ST[k].rc].led;

}
void query(int l, int r, int k) {
    if(ST[k].l > r || ST[k].r < l)
        return ;
    if(ST[k].l >= l && ST[k].r <= r) {
        f0 = max(ST[k].midmax, f1 + ST[k].lmax);
        if(ST[k].midmax == f0 && f1 + ST[k].lmax != f0)
            st0 = ST[k].mst, ed0 = ST[k].med;
        else if(f1 + ST[k].lmax == f0 && ST[k].midmax != f0)
            st0 = st1, ed0 = ST[k].led;
        else {
            if(ST[k].mst < st1 || (ST[k].mst == st1 && ST[k].med < ST[k].led))
                st0 = ST[k].mst, ed0 = ST[k].med;
            else
                st0 = st1, ed0 = ST[k].led;
        }
        int pref1 = f1;
        f1 = max(ST[k].rmax, f1 + ST[k].sum);
        if(ST[k].rmax == f1 && pref1 + ST[k].sum != f1)
            st1 = ST[k].rst, ed1 = ST[k].red;
        else if(pref1 + ST[k].sum == f1 && ST[k].rmax != f1)
            st1 = st1, ed1 = ST[k].r;
        else {
            if(ST[k].rst < st1 || (ST[k].rst == st1 && ST[k].red < ST[k].r))
                st1 = ST[k].rst, ed1 = ST[k].red;
            else
                st1 = st1, ed1 = ST[k].r;
        }

        if(f0 > Ans || (f0 == Ans && st > st0 || (st == st0 && ed > ed0))) Ans = f0, st = st0, ed = ed0;
        if(f1 > Ans || (f1 == Ans && st > st1 || (st == st1 && ed > ed1))) Ans = f1, st = st1, ed = ed1;
        return ;
    }
    query(l, r, ST[k].lc), query(l, r, ST[k].rc);
}
int Input() {
    char cha;
    unsigned int x = 0;
    while(cha = getchar())
        if(cha != ' ' && cha != '\n' || cha == EOF) break;
    if(cha == EOF) return -1;
    x = cha-48;
    while(cha = getchar()) {
        if(cha == ' ' || cha == '\n') break;
        x = x*10 + cha-48;
    }
    return x;
}
main() {
    int n, Q, a, C = 0;
    int i, j;
    while(scanf("%d %d", &n, &Q) == 2) {
        for(a = 1; a <= n; a++)
            scanf("%lld", &A[a]);
        init(1, n, 1);
        printf("Case %d:\n", ++C);
        while(Q--) {
            i = Input(), j = Input();
            f0 = f1 = 0, Ans = -(1LL<<60), st0 = st1 = ed0 = ed1 = i;
            query(i, j, 1);
            printf("%d %d\n", st, ed);
        }
    }
    return 0;
}
