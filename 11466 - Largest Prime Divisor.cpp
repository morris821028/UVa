#include <stdio.h>
#include <math.h>
const int N = 10000000;
unsigned mark[(N>>5)+1];
int prime[670000], pt = 0;
int GET(int x) {
    return mark[x>>5]>>(x&31)&1;
}
void SET(int x) {
    mark[x>>5] |= 1<<(x&31);
}
void sieve() {
    register int i, j;
    int sqr = N;
    SET(0), SET(1);
    for(i = 2; i <= sqr; i++) {
        if(!GET(i)) {
            prime[pt++] = i;
            for(j = i+i; j <= N; j += i)
                SET(j);
        }
    }
}
void solve(long long n) {
    int i, cnt = 0;
    long long pre = n, ans = -1;
    for(i = 0; prime[i] <= sqrt(n) && i < pt; i++) {
        if(n%prime[i] == 0) {
            ans = prime[i];
            cnt++;
            while(n%prime[i] == 0)
                n /= prime[i];
        }
    }
    if(n != 1)
        ans = n, cnt++;
    if(cnt <= 1)
        ans = -1;
    printf("%lld\n", ans);
}
int main() {
    sieve();
    long long n;
    while(scanf("%lld", &n) == 1 && n) {
        if(n < 0)   n *= -1;
        if(n <= N && GET(n) == 0)
            puts("-1");
        else
            solve(n);
    }
    return 0;
}
