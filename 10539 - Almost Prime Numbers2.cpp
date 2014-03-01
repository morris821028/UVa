#include <stdio.h>
#include <algorithm>
#include <vector>
#define maxN 1000000000000LLU
#define maxL (1000000>>5)+1
using namespace std;
int p[80000], pt = 0;
int mark[maxL];
int GET(int x) {    return mark[x>>5]>>(x&31)&1;}
void SET(int x) {    mark[x>>5] |= 1<<(x&31);}
void sieve() {
    int i, j, k;
    int n = 1000000;
    for(i = 2; i <= n; i++) {
        if(!GET(i)) {
            for(k = n/i, j = i*k; k >= i; k--, j -= i)
                SET(j);
            p[pt++] = i;
        }
    }
}
long long APN[100000];
int at = 0;
void build() {
    int i;
    for(i = 0; i < pt; i++) {
        long long tmp = (long long)p[i]*p[i];
        while(tmp <= maxN) {
            APN[at++] = tmp;
            tmp = tmp*p[i];
        }
    }
}
int main() {
    sieve();
    build();
    int t;
    long long a, b;
    sort(APN, APN+at);
    vector<long long> v(APN, APN+at);
    scanf("%d", &t);
    while(t--) {
        scanf("%lld %lld", &a, &b);
        int cnt = 0, i;
        vector<long long>::iterator low, up;
        low = lower_bound(v.begin(), v.end(), a);
        up = upper_bound(v.begin(), v.end(), b);
        int l = low-v.begin();
        int r = up-v.begin();
        printf("%d\n", r-l);
    }
    return 0;
}
