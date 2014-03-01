#include <stdio.h>
#include <math.h>

int main() {
    int n, i, j;
    scanf("%*d");
    while(scanf("%d", &n) == 1) {
        int f[50] = {}, tmp;
        f[0] = 1;
        for(i = 2; ; i++) {
            for(j = 0; j < n; j++) {
                tmp = f[j]+i;
                tmp = (int)sqrt(tmp);
                if(tmp*tmp == f[j]+i || f[j] == 0) {
                    f[j] = i;
                    break;
                }
            }
            if(j == n)  break;
        }
        printf("%d\n", i-1);
    }
    return 0;
}
