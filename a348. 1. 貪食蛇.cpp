#include <stdio.h>
int main() {
    int m, i;
    while(scanf("%d", &m) == 1 && m) {
        for(i = 0; ; i++)
            if(i*i >= m)
                break;
        int n = i-1;
        if(n&1) {
            if(m - n*n <= n+1)
                printf("%d %d\n", m - n*n, n+1);
            else
                printf("%d %d\n", n+1, 2*n + 2 - m + n*n);
        } else {
            if(m - n*n <= n+1)
                printf("%d %d\n", n+1, m - n*n);
            else
                printf("%d %d\n", 2*n + 2 - m + n*n, n+1);
        }
    }
    return 0;
}
