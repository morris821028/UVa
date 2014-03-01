#include <stdio.h>
#include <algorithm>
using namespace std;
#define maxL (1000>>5)+1
#define GET(x) (mark[(x)>>5]>>((x)&31)&1)
#define SET(x) (mark[(x)>>5] |= 1<<((x)&31))
int mark[maxL];
int pm[1000], pt = 0;
void sieve() {
    register int i, j, k;
    SET(1);
    int n = 1000;
    for(i = 2; i <= n; i++) {
        if(!GET(i)) {
            pm[pt++] = i;
            for(k = n/i, j = i*k; k >= i; k--, j -= i)
                SET(j);
        }
    }
}
int f[1000], fidx, ret;
int n, m;
int i, j, k;
void dfs(int idx, long long mult) {
    if(idx == fidx) return;
    for(; mult <= ret; mult *= f[idx]) {
        dfs(idx+1, mult);
        if(mult > n)
            ret = min(ret, (int)mult);
    }
}
int main() {
    sieve();
    while(scanf("%d", &n) == 1) {
        if(n < 2) {
            puts("Not Exist!");
            continue;
        }
        m = n;
        fidx = 0;
        int base = 1;
        for(i = 0; i < pt && pm[i]*pm[i] <= m; i++) {
            j = pm[i];
            if(m%j == 0) {
                k = 0;
                while(m%j == 0) k++, m /= j;
                f[fidx++] = j, base *= j;
            }
        }
        if(fidx == 0) {//prime
            if(n > 1414)
                puts("Not Exist!");
            else
                printf("%d\n", n*n);
            continue;
        }
        if(m != 1)
            f[fidx++] = m, base *= m;
        ret = 2000000;
        dfs(0, base);
        if(ret < 2000000)
            printf("%d\n", ret);
        else
            puts("Not Exist!");
    }
    return 0;
}
