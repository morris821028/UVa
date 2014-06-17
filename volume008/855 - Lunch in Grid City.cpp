#include <stdio.h>
inline int ReadInt(int *x) {
    static char c, neg;
    while((c = getchar()) < '-')    {if(c == EOF) return EOF;}
    neg = (c == '-') ? -1 : 1;
    *x = (neg == 1) ? c-'0' : 0;
    while((c = getchar()) >= '0')
        *x = (*x << 3) + (*x << 1) + c-'0';
    *x *= neg;
    return 1;
}
int main() {
    int t, R, C, P, i, j, A;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d %d", &R, &C, &P);
        long long x[1001] = {}, y[1001] = {}, sum;
        while(P--) {
            scanf("%d %d", &i, &j);
            x[i]++, y[j]++;
        }
        for(i = 1; i <= C; i++)
            y[i] += y[i-1];
        for(i = 1; i <= R; i++)
            x[i] += x[i-1];
        int ax = 1, ay = 1;
        long long ans, tmp = 0;
        long long tot = 0;
        for(i = 1; i <= R; i++)
            tmp += (i-1)*(x[i]-x[i-1]);
        ans = tmp;
        for(i = 2; i <= R; i++) {
            tmp = tmp + x[i-1] - (x[R]-x[i-1]);
            if(tmp < ans)
                ans = tmp, ax = i;
        }
        tot += ans, tmp = 0;
        for(i = 1; i <= C; i++)
            tmp += (i-1)*(y[i]-y[i-1]);
        ans = tmp;
        for(i = 2; i <= C; i++) {
            tmp = tmp + y[i-1] - (y[C]-y[i-1]);
            if(tmp < ans)
                ans = tmp, ay = i;
        }
        tot += ans;
        printf("(Street: %d, Avenue: %d)\n", ax, ay);
    }
    return 0;
}
