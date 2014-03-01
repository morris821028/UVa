#include <stdio.h>

int main() {
    int a, b, c, d;
    while(scanf("%d %d", &a, &b) == 2) {
        scanf("%d %d", &c, &d);
        if(a+b+c+d == 0)    break;
        int time = a*60+b, cnt = 0;
        for(;; time++) {
            a = time/60, b = time%60;
            if(a == 24 && b == 0)   time = 0, a = 0;
            if(a == c && b == d)    break;
            cnt++;
        }
        printf("%d\n", cnt);
    }
    return 0;
}
