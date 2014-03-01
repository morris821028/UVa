#include <stdio.h>
#include <string.h>
long long mpow(long long x, long long y, long long mod) {
    if(y == 0)  return 1;
    if(y&1)
        return x*mpow(x*x%mod, y/2, mod)%mod;
    return mpow(x*x%mod, y/2, mod);
}
int cycle[101];
void findcycle() {
    int i, j;
    for(i = 0; i < 10; i++) {
        for(j = i*10+1; j <= i*10+10; j++) {
            cycle[j] = cycle[j-1]+mpow(j, j, 10);
            //printf("%lld ", mpow(j, j, 10));
        }
    }
}
int main() {
    findcycle();
    char s[200];
    while(scanf("%s", s) == 1) {
        if(s[0] == '0' && s[1] == '\0')
            break;
        int n;
        if(strlen(s) > 5)
            sscanf(s+strlen(s)-5, "%d", &n);
        else
            sscanf(s, "%d", &n);
        printf("%d\n", (cycle[n%100])%10);
    }
    return 0;
}
