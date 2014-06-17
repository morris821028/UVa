#include <stdio.h>
#define LL long long
LL mpow(LL x, LL y, LL mod) {
    if(!y)  return 1;
    if(y&1)
        return x*mpow(x*x%mod, y/2, mod)%mod;
    return mpow(x*x%mod, y/2, mod);
}
int main() {
    char s[10005];
    int cases = 0;
    int i, j, aflag;
    while(scanf("%s", s) == 1 && s[0] != '.') {
        i = 1;
        long long ai, p, sign, D;
        long long a[1000], b[1000], idx = 0;
        while(s[i] != ')') {
            sign = 1;
            if(s[i] == '+') i++, sign = 1;
            if(s[i] == '-') i++, sign = -1;
            ai = 0, aflag = 0;
            while(s[i] >= '0' && s[i] <= '9')
                ai = ai*10 + s[i]-'0', i++, aflag = 1;
            if(aflag == 0)  ai = 1;
            if(s[i] == 'n') {
                i++, p = 0;
                if(s[i] == '^') {
                    i++;
                    while(s[i] >= '0' && s[i] <= '9')
                        p = p*10 + s[i]-'0', i++;
                } else
                    p = 1;
            } else {
                p = 0;
            }
            ai = ai*sign; // (ai)n^p
            a[idx] = ai, b[idx] = p;
            idx++;
        }
        sscanf(s+i+2, "%lld", &D);
        int ok = 1;
        for(i = 0; i < 150 && ok; i++) {
            long long sum = 0;
            for(j = 0; j < idx; j++) {
                sum += a[j]*mpow(i, b[j], D);
                sum %= D;
            }
            if(sum)
                ok = 0;
        }
        printf("Case %d: ", ++cases);
        if(ok)  puts("Always an integer");
        else    puts("Not always an integer");
    }
    return 0;
}
