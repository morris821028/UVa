#include <stdio.h>
#include <math.h>
long double LOG[100005];
int main() {
    int i, p, q, r, s;
    for(i = 1; i <= 100000; i++)
        LOG[i] = log(i);
    while(scanf("%d %d %d %d", &p, &q, &r, &s) == 4) {
        long double ans = 0;
        if(p-q < q) q = p-q;
        if(r-s < s) s = r-s;
        for(i = 1; i <= q; i++)
            ans += LOG[p-q+i] - LOG[i];
        for(i = 1; i <= s; i++)
            ans += -LOG[r-s+i] + LOG[i];
        printf("%.5lf\n", exp(ans));
    }
    return 0;
}
