#include <stdio.h>

int main() {
    int n;
    while(scanf("%d", &n) == 1 && n) {
        int a = 0, b = 0, flag = 0;
        while(n&(-n)) {
            if(flag)
                a |= n&(-n);
            else
                b |= n&(-n);
            n -=  n&(-n);
            flag = !flag;
        }
        printf("%d %d\n", b, a);
    }
    return 0;
}
