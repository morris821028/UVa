#include <stdio.h>
int mypow(int x, int y, int mod) {
    if(!y)   return 1;
    if(y&1)
        return x*mypow(x*x%mod, y>>1, mod)%mod;
    return mypow(x*x%mod, y>>1, mod);
}
int main() {
    int n, m, tmp, i;
    while(scanf("%d %d", &n, &m) == 2) {
        if(n == 1)  printf("%d\n", 14%m);
        else if(n == 2)  printf("%d\n", 155%m);
        else if(n == 3)  printf("%d\n", 1575%m);
        else {
            tmp = 1575%m;
            tmp = tmp*mypow(10, n-3, m)%m;
            printf("%d\n", tmp);
        }
    }
    return 0;
}
/*
14
155
1575
15750
157500
*/
