#include <stdio.h>
#include <algorithm>
using namespace std;
int main() {
    int n, an1;
    while(scanf("%d %d", &n, &an1) == 2) {
        long long a[50][50] = {};
        int i, j, k;
        a[n][1] = an1;
        for(i = n; i >= 1; i--) {
            for(j = 1; j <= n; j++) {
                if(i == n && j == 1)    continue;
                if(i >= j) {
                    long long v1 = 0, v2 = 0;
                    for(k = i+1; k <= n; k++)
                        v1 = max(v1, a[k][1]+a[k][j]);
                    for(k = 1; k < j; k++)
                        v2 = max(v2, a[i][k]+a[n][k]);
                    a[i][j] = v1 + v2;
                } else {
                    long long &v = a[i][j];
                    v = 0;
                    for(k = i; k < j; k++)
                        v = max(v, a[i][k]+a[k+1][j]);
                }
            }
        }
        printf("%lld\n", a[1][n]);
    }
    return 0;
}
