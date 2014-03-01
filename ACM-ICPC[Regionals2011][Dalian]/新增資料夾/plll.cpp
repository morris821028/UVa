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
int p[35], pt = 0;
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
    return ((((n*(n+1)%MOD)*(n*2+1))%MOD*((n*n%MOD*3%MOD+n*3%MOD-1)%MOD))%MOD)%MOD*inv30%MOD;
}
void dfs(int idx, int cnt, int num) {
    if(idx == pt) {
        if(cnt == 0)    return;
        long long base = (long long)num*num%MOD*num%MOD*num%MOD;
        long long i = on/num;
        if(cnt&1) {
            ans -= base*n44(i);
           // printf("- %lld %lld\n", base*n44(i), i);
        } else {
            ans += base*n44(i);
            // printf("+ %lld\n", base*n44(i));
        }
        ans %= MOD;
        return;
    }
    dfs(idx+1, cnt+1, num*p[idx]);
    dfs(idx+1, cnt, num);
}

int gcd(int a,int b)
{
    return b?gcd(b,a%b):a;
}

int main(){
    int t, i;
    inv30 = inv(30, MOD-2);
    /*t = 1000;
    while(t--)
    {
        int fh1 = (rand()*rand()%MOD+MOD)%MOD;
        ll s = 0;
        for(int fh2=1;fh2<=fh1;fh2++)
            if(gcd(fh1,fh2)==1)
                s+=((long long)fh2*fh2%MOD*fh2%MOD*fh2%MOD), s%=MOD;
        s = (s+MOD)%MOD;
        cout<<"h1 "<<fh1<<' '<<s<<endl;
        n = fh1;
        int sq = (int)sqrt(n);
        on = n;
        ans = n44(n)%MOD;
        pt = 0;
        for(i = 2; i <= sq; i++) {
            if(n%i == 0) {
                p[pt++] = i;
                printf("%d ", i);
                while(n%i == 0)
                    n /=i ;
            }
        }
        if(n != 1)  {
            p[pt++] = n;
            printf("%d ", n);
        }
        puts("");

        dfs(0, 0, 1);
        ans = (ans%MOD+MOD)%MOD;
        printf("%lld\n", ans);
        if(ans != s)
            break;
        else
            puts("PASS");
    }*/
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
