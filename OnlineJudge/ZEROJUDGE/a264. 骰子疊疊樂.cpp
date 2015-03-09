#include <stdio.h>

int main() {
    int n;
    while(scanf("%d", &n) == 1) {
        if(n < 21)  puts("-1");
        else if(n == 21)    puts("1");
        else {
            if(n < 30)  puts("-1");
            else {
                int m = (n-30)/14*14 + 30;
                if(n >= m && n <= m + 10)
                    printf("%d\n", (n-30)/14+2);
                else
                    puts("-1");
            }
        }
    }
    return 0;
}
