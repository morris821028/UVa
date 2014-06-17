#include <stdio.h>
#include <algorithm>
using namespace std;
#define maxL (2000000>>5)+1
#define GET(x) (mark[(x)>>5]>>((x)&31)&1)
#define SET(x) (mark[(x)>>5] |= 1<<((x)&31))
int mark[maxL];
struct E {
    int n, pi;
    bool operator<(const E &a) const {
        if(pi != a.pi)
            return pi < a.pi;
        return n < a.n;
    }
};
E D[2000005];
int S[2000005];
void sieve() {
    register int i, j, k;
    SET(1);
    int n = 2000000;
    for(i = 2; i <= n; i++)
        D[i].n = i, D[i].pi = 1;
    for(i = 2; i <= n; i++) {
        if(!GET(i)) {
            D[i].pi = i;
            for(k = n/i, j = i*k; k >= 2; k--, j -= i) {
                D[j].pi *= i;
                SET(j);
            }
        }
        S[i] = D[i].pi;
    }
    D[0].pi = 0;
    D[1].pi = 1;
}
int main() {
    sieve();
    long long n;
    return 0;
    sort(D, D+2000001);
    int i;
    while(scanf("%lld", &n) == 1) {
        if(n < 2) {
            puts("Not Exist!");
            continue;
        }
        E test;
        test.n = n, test.pi = S[n];
        int pos = upper_bound(D, D+2000001, test) - D;
        if(pos <= 2000000 && D[pos].pi == test.pi)
            printf("%d\n", D[pos].n);
        else
            puts("Not Exist!");
    }
    return 0;
}
