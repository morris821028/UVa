#include <stdio.h>
#include <math.h>
#define LL long long
#define mod 2147483647LL
LL inverse(LL x, LL p) {
    if(!p)  return 1;
    if(p&1) return x*inverse((x*x)%mod, p>>1)%mod;
    return inverse((x*x)%mod, p>>1);
}
int doubleDet(int n, float A[][35]) {
    int inch = 0, i, j, k;
    float tmp;
    for(i = 0; i < n; i++) {
        int ch = -1;
        for(j = i; j < n; j++) {
            if(fabs(A[j][i]) >= 1e-6) {
                ch = j; break;
            }
        }
        if(ch == -1)
            return 0;
        if(i != ch) {
            for(j = i; j < n; j++)
                tmp = A[i][j], A[i][j] = A[ch][j], A[ch][j] = tmp;
            inch++;
        }
        LL inv, sub;
        for(j = i+1; j < n; j++) {
            if(fabs(A[j][i]) < 1e-6)  continue;
            tmp = A[j][i]/A[i][i];
            for(k = 0; k < n; k++) {
                A[j][k] = A[j][k] - A[i][k]*tmp;
            }
        }
    }
    tmp = 1;
    if(inch&1)  tmp *= -1;
    for(i = 0; i < n; i++)
        tmp *= A[i][i];
    return tmp > 0 ? 1 : -1;
}
int main() {
    int n, i, j, k;
    LL mix[35][35] = {}, tmp;
    float A[35][35] = {};
    while(scanf("%d", &n) == 1 && n) {
        for(i = 0; i < n; i++) {
            for(j = 0; j < n; j++) {
                scanf("%lld", &mix[i][j]);
                mix[i][j] = (mix[i][j]+mod)%mod;
                A[i][j] = mix[i][j];
            }
        }
        int inch = 0;
        for(i = 0; i < n; i++) {
            int ch = -1;
            for(j = i; j < n; j++) {
                if(mix[j][i]) {
                    ch = j; break;
                }
            }
            if(ch == -1 || !mix[ch][i]) {
                puts("0");  break;
            }
            if(i != ch) {
                for(j = i; j < n; j++)
                    tmp = mix[i][j], mix[i][j] = mix[ch][j], mix[ch][j] = tmp;
                inch++;
            }
            LL inv, sub;
            for(j = i+1; j < n; j++) {
                if(mix[j][i] == 0)  continue;
                inv = inverse(mix[i][i], mod-2);
                sub = (mix[j][i]*inv)%mod;
                for(k = 0; k < n; k++) {
                    mix[j][k] = mix[j][k] - sub*mix[i][k]%mod;
                    mix[j][k] = (mix[j][k]+mod)%mod;
                }
            }
        }
        if(i != n)  continue;
        LL ans = 1;
        for(i = 0; i < n; i++) {
            ans *= mix[i][i];
            ans %= mod;
        }
        if(inch&1)  ans *= -1;
        ans = (ans+mod)%mod;
        if(ans == 0 || doubleDet(n, A) >= 0)
            printf("%lld\n", ans);
        else
            printf("%lld\n", -(mod-ans));
    }
    puts("*");
    return 0;
}
