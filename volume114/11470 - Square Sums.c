#include <stdio.h>

int main() {
    int n, Case = 0, i, j;
    while(scanf("%d", &n) == 1 && n) {
        int sum[10] = {}, x;
        for(i = 0; i < n; i++) {
            for(j = 0; j < n; j++) {
                scanf("%d", &x);
                if(j < n-i) {
                    int min = i < j ? i : j;
                    sum[min] += x;
                } else {
                    int max = i > j ? i : j;
                    sum[n-max-1] += x;
                }
            }
        }
        printf("Case %d:", ++Case);
        for(i = 0; i < n/2+n%2; i++) {
            printf(" %d", sum[i]);
        }
        puts("");
    }
    return 0;
}
