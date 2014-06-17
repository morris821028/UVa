#include <stdio.h>

int main() {
    int n, k, i, j;
    int a[150];
    while(scanf("%d", &n) == 1 && n) {
        for(i = 0; i < n; i++)
            scanf("%d", &a[i]);
        scanf("%d", &k);
        for(j = n-1; j >= 0; j--)
            for(i = 0; i < j; i++)
                a[i] = a[i+1] - a[i];
        for(j = 0; j < k; j++)
            for(i = 1; i < n; i++)
                a[i] += a[i-1];
        printf("Term %d of the sequence is %d\n", n+k, a[n-1]);
    }
    return 0;
}
