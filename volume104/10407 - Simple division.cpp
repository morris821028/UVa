#include <stdio.h>
#include <stdlib.h>
int gcd(int x, int y) {
    if(!x)  return y;
    if(!y)  return x;
    int t;
    while(x%y) {
        t = x, x = y, y = t%y;
    }
    return y;
}
int main() {
    int a[1000];
    while(scanf("%d", a) == 1) {
        if(a[0] == 0)
            break;
        int n = 1, i;
        while(scanf("%d", a+n) == 1) {
            if(a[n] == 0)
                break;
            n++;
        }
        int ans = abs(a[1]-a[0]);
        for(i = 2; i < n; i++) {
            ans = gcd(ans, abs(a[i]-a[i-1]));
        }
        printf("%d\n", ans);
    }
    return 0;
}
