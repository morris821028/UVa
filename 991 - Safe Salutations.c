#include <stdio.h>

int main() {
    int f[11] = {1, 1}, i, j;
    for(i = 2; i <= 10; i++)
        for(j = 0; j < i; j++)
            f[i] += f[j]*f[i-j-1];
    int n, flag = 0;
    while(scanf("%d", &n) == 1) {
        if(flag)
            puts("");
        flag = 1;
        printf("%d\n", f[n]);
    }
    return 0;
}
