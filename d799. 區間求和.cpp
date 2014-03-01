#include<stdio.h>
#define N 524288
struct segment {
    int l, r;
    long long sum, add;
}ST[2*N + 2];
int A[N + 1], m;
void init(int l, int r) {
    int a;
    for(a = 2*m - 1; a > 0; a--) {
        if(a >= m) { /*葉節點*/
            ST[a].sum = A[a-m];
            ST[a].l = ST[a].r = a-m;
        }
        else { /*分支節點*/
            ST[a].sum = ST[a<<1].sum + ST[(a<<1)+1].sum;
            ST[a].l = ST[a<<1].l;
            ST[a].r = ST[(a<<1)+1].r;
        }
    }
}
long long query(int l, int r) {
    long long sum;
    int num_l, num_r;
    sum = num_l = num_r = 0;
    for(l = l+m-1, r = r+m+1; (l^r) != 1;) {
        if(~l&1) {
            sum += ST[l^1].sum;
            num_l += (ST[l^1].r - ST[l^1].l + 1);
        }
        if(r&1) {
            sum += ST[r^1].sum;
            num_r += (ST[r^1].r - ST[r^1].l + 1);
        }
        l >>= 1, r >>= 1;
        sum += num_l*ST[l].add;
        sum += num_r*ST[r].add;
    }
    
    for(l >>= 1; l > 0; l >>= 1) {
        sum += (num_l+num_r)*ST[l].add;
    }
    return sum;
}
void add(int l, int r, int k) {
    int num_l, num_r;
    num_l = num_r = 0;
    for(l = l+m-1, r = r+m+1; (l^r) != 1;) {
        if(~l&1) {
            ST[l^1].add += k;
            ST[l^1].sum += (ST[l^1].r - ST[l^1].l + 1)*k;
            num_l += (ST[l^1].r - ST[l^1].l + 1);
        }
        if(r&1) {
            ST[r^1].add += k;
            ST[r^1].sum += (ST[r^1].r - ST[r^1].l + 1)*k;
            num_r += (ST[r^1].r - ST[r^1].l + 1);
        }
        l >>= 1, r >>= 1;
        ST[l].sum += num_l*k;
        ST[r].sum += num_r*k;
    }
    for(l >>= 1; l > 0; l >>= 1) {
        ST[l].sum += (num_l + num_r)*k;
    }
}
int Input() { 
    char cha; 
    unsigned int x = 0; 
    while(cha = getchar()) 
        if(cha != ' ' && cha != '\n') break; 
    x = cha-48; 
    while(cha = getchar()) { 
        if(cha == ' ' || cha == '\n') break; 
        x = x*10 + cha-48; 
    } 
    return x; 
}
main() {
    int n, a, q, i, j, k;
    char v;
    while(scanf("%d", &n) == 1) {
        for(a = 1; a <= n; a++)
            A[a] = Input();
        for(m = 1; m < (n+2); m <<= 1) ;
        init(0, m-1);
        scanf("%d", &q);
        getchar();
        while(q--) {
            v = getchar();
            if(v == '1')
                i = Input(), j = Input(), k = Input(), add(i, j, k);
            else
                i = Input(), j = Input(), printf("%lld\n", query(i, j));
        }
    }
    return 0;
}
