#include <stdio.h>

int main() {
    int t, n;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        int sum = 0, k = 0, i, x;
        for(i = 0; i < n; i++) {
            scanf("%d", &x);
            sum += x;
            if(sum == 0)
                k++;
        }
        printf("%d\n", k);
    }
    return 0;
}
