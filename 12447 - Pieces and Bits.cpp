#include <stdio.h>
int main() {
    int t, n, i, j;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        int num = 0, times = 0;
        while(true) {
            printf("%d\n", num);
            for(i = 0; i < n; i++)
                if(!((times>>i)&1))
                    break;
            if(i == n)  break;
            num = ((1<<n)-1) ^ num ^ (1<<i);
            times++;
        }
    }
    return 0;
}
