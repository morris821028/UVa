#include <stdio.h>
#include <math.h>
int main() {
    int t, n, i, j, k;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        int sq = (int)sqrt(n), sq2;
        int ans = 0xfffffff;
        for(i = 1; i <= sq; i++) {
            if(n%i == 0) {
                j = n/i;
                sq2 = (int)sqrt(j);
                for(k = 1; k <= sq2; k++) {
                    if(j%k == 0) {
                        int tmp = 2*(i*k + j + i*j/k);
                        if(tmp < ans)
                            ans = tmp;
                    }
                }
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
