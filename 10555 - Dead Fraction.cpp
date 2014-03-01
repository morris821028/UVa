#include <stdio.h>
#define LL long long
LL gcd(LL x, LL y) {
    LL t;
    while(x%y)
        t = x, x = y, y = t%y;
    return y;
}
LL mpow(LL x, LL y) {
    if(y == 0)  return 1;
    if(y&1) return x*mpow(x*x, y>>1);
    return mpow(x*x, y>>1);
}
int main() {
    char s[105];
    int i;
    while(scanf("%s", s) == 1) {
        if(s[1] == '\0')
            break;
        for(i =  2; s[i]; i++)
            if(s[i] == '.')
                break;
        s[i] = '\0';
        int a = i-2, t;
        LL x, y, ax, ay, g, tx, ty;
        y = mpow(10, a)-1;
        sscanf(s+2, "%lld", &x);
        g = gcd(x, y);
        ax = x/g, ay = y/g;
        for(i = 2; i < a+1; i++) {
            t = s[i+1];
            s[i+1] = '\0';
            sscanf(s+2, "%lld", &x);
            s[i+1]  = t;
            sscanf(s+i+1, "%lld", &y);
            ty = mpow(10, i-1)*(mpow(10, a-i+1)-1);
            tx = x*(mpow(10, a-i+1)-1)+y;
            g = gcd(tx, ty);
            tx /= g, ty /= g;
            if(ty < ay) ax = tx, ay = ty;
            //printf("%lld %lld %d %d %lld/%lld\n", x, y, i-1, a-i+1, tx, ty);
        }
        printf("%lld/%lld\n", ax, ay);
    }
    return 0;
}
