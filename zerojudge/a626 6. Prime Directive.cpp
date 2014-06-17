#include <stdio.h>

int main() {
    int n, i, j, k;
    while(scanf("%d", &n) == 1) {
        for(i = 2, k = 0; i <= n; i++) {
            for(j = 2; j*j <= i; j++)
                if(i%j == 0)    break;
            if(j*j > i) {
                printf("%10d", i), k++;
                if(k == 5)  puts(""), k = 0;
            }
        }
        if(k)   puts("");
    }
    return 0;
}
