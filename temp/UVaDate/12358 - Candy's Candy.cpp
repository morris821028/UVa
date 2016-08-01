#include <stdio.h>
#include <algorithm>
using namespace std;

const int MAXN = 131072;
int n, A[MAXN];
long long f(int pack_size) {            // #candy of different flavors in the variety pack
    if (A[0] / pack_size <= n) return 0;
//    printf("pack_size %d\n", pack_size);
    int vpack = A[0] / pack_size % n;   // #variety pack >= vpack
    for (int i = 0; i < n; i++) {
        if (A[i] / pack_size %n != vpack)
            return 0;
    }
    long long pcnt = A[0] / pack_size / n;
    if (vpack == 0)                     // at least one variety pack.
        pcnt--;                         // open one flavored pack to make n vpariety pack.
    return pcnt;
}
int main() {
    while (scanf("%d", &n) == 1 && n) {
        for (int i = 0; i < n; i++)
            scanf("%d", &A[i]);
        
        sort(A, A + n);
        int g = A[0];
        long long ret = 0;
        for (int i = 0; i < n; i++)
            g = __gcd(g, A[i]);
        
        for (int i = 1; i * i <= g; i++) {
            if (g%i == 0) {
                ret += f(i);
                if (i * i != g)
                    ret += f(g / i);
            }
        }
        printf("%lld\n", ret);
    }
    return 0;
}

/*
 3
 15 33 21
 2
 1 1
 2
 2 2
 2
 3 3
 3
 1000000000 1000000000 1000000000

*/