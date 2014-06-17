#include <stdio.h>
#include <math.h>

int main() {
    char s[50];
    int i, j, k, n, m, p, cases = 0;
    gets(s);
    while(gets(s)) {
        sscanf(s, "%d", &n);
        for(i = 0, m = 0; s[i]; i++)
            if(s[i] == '!') m++;
        int C[1005] = {};
        for(i = n; i >= 0; i -= m) {
            p = i;
            for(j = 2; j <= p; j++) {
                while(p%j == 0)
                    p /= j, C[j]++;
            }
        }
        long long res = 1;
        double sum = 0;
        for(i = 0; i <= n; i++)
            res *= C[i]+1, sum += log10(C[i]+1);
        printf("Case %d: ", ++cases);
        if(ceil(sum) > 18)
            puts("Infinity");
        else
            printf("%lld\n", res);
    }
    return 0;
}
