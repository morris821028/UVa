#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<cstdlib>
#include <math.h>
#include<map>
#define mem(x) memset(x,0,sizeof(x))
using namespace std;

typedef long long ll;

#define MOD 1000000007LL
int p[30], pt = 0;
int n, on;
long long inv(long long x, long long y) {
    if(y == 0)  return 1;
    if(y&1) {
        return x*inv(x*x%MOD, y/2)%MOD;
    } else {
        return inv(x*x%MOD, y/2);
    }
}
long long ans, inv30;
long long n44(long long n) {
    return n*(n+1)%MOD*(n*2+1)%MOD*(n*n*3%MOD+n*3-1)%MOD*inv30%MOD;
}
void dfs(int idx, int cnt, int num) {
    if(idx == pt) {
        if(cnt == 0)    return;
        long long base = (long long)num*num%MOD*num%MOD*num%MOD;
        long long i = on/num;
        if(cnt&1) {
            ans -= base*n44(i);
        } else {
            ans += base*n44(i);
        }
        ans %= MOD;
        return;
    }
    dfs(idx+1, cnt+1, num*p[idx]);
    dfs(idx+1, cnt, num);
}
int main(){
    int t, i;
    inv30 = inv(30, MOD-2);
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        int sq = (int)sqrt(n);
        on = n;
        pt = 0;
        for(i = 2; i <= sq; i++) {
            if(n%i == 0) {
                p[pt++] = i;
                while(n%i == 0)
                    n /=i ;
            }
        }
        if(n != 1)  p[pt++] = n;
        ans = n44(on)%MOD;
        dfs(0, 0, 1);
        printf("%lld", (ans%MOD+MOD)%MOD);
        puts("");
    }
    return 0;
}
