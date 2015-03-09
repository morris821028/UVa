#include <stdio.h>

int main() {
    double n, s;
    int i;
    while(scanf("%lf", &n) == 1) {
        for(i = 2, s = 0; ; i++) {
            s += 1.0/i;
            if(s >= n)  break;
        }
        printf("%d card(s)\n", i-1);
    }
    return 0;
}
