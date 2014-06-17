#include <stdio.h>
#define LL long long
#define FOR(i,x,y) for(i=x;i<y;i++)
#define mod 100000007LL
#define SWAP(T,A,B) {T t;t=A,A=B,B=t;}
LL inv(LL x, LL p) {
    if(!p)  return 1;
    if(p&1) return x*inv((x*x)%mod, p/2)%mod;
    return inv((x*x)%mod, p/2);
}
LL mix[15][15], sub, ans;
int n, i, j, k, inch, ch;
LL sol() {
    inch = 0, ans = 1;
    FOR(i,0,n) {
        ch = i;
        FOR(j,i,n)  if(mix[j][i]) {ch = j; break;}
        if(!mix[ch][i]) return 0;
        if(i != ch) {
            FOR(j,i,n)  SWAP(LL,mix[i][j],mix[ch][j]);
            inch++;
        }
        FOR(j,i+1,n) {
            if(!mix[j][i])  continue;
            sub = (mix[j][i]*inv(mix[i][i], mod-2))%mod;
            FOR(k,i,n)
                mix[j][k] = (mix[j][k]-sub*mix[i][k]%mod+mod)%mod;
        }
        ans = (ans*mix[i][i])%mod;
    }
    if(inch&1)  ans *= -1;
    return (ans+mod)%mod;
}
int main() {
    while(scanf("%d", &n) == 1) {
        FOR(i,0,n) {
            FOR(j,0,n) {
                scanf("%lld", &mix[i][j]);
                mix[i][j] = (mix[i][j]+mod)%mod;
            }
        }
        printf("%lld\n", sol());
    }
    return 0;
}
