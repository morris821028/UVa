#include <stdio.h>
#include <math.h>
int p[5200], pt = 0;
int N[100000];
void sieve() {
    int i, j, mark[50000] = {};
    for(i = 2; i < 50000; i++) {
        if(!mark[i]) {
            p[pt++] = i;
            for(j = i+i; j < 50000; j += i)
                mark[j] = 1;
        }
    }
}
int NOD(int n) {
    int ans = 1, cnt = 0, i;
    for(i = 0; i < pt && p[i]*p[i] <= n; i++) {
        if(n%p[i] == 0) {
            cnt = 0;
            while(n%p[i] == 0)
                cnt++, n /= p[i];
            ans *= cnt+1;
        }
    }
    if(n != 1)  ans *= 2;
    return ans;
}
int build() {
    N[0] = 1;
    int i;
    for(i = 1; ; i++) {
        N[i] = N[i-1] + NOD(N[i-1]);
        if(N[i] > 1000000)
            return i;
    }
}
int main() {
    sieve();
    int R = build(), L = 0;
    int t, cases = 0, A, B;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &A, &B);
        int l = L, r = R, m, x, y;
        while(l < r) {
            m = (l+r)>>1;
            if(N[m] < A)
                l = m+1;
            else
                r = m;
        }
        x = l;
        l = L, r = R;
        while(l < r) {
            m = (l+r)>>1;
            if(N[m] < B)
                l = m+1;
            else
                r = m;
        }
        y = l + (N[l] == B);
        printf("Case %d: %d\n", ++cases, y-x);
    }
    return 0;
}
