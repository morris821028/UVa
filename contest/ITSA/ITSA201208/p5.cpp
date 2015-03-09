#include <stdio.h>
#include <stdlib.h>
int mm[13] = {0,0,31,59,90,120,151,181,212,243,273,304,334};
int cntDay(int y, int m, int d) {
    int lp, islp = 0;
    if(y%4 == 0 && y%100 != 0 || y%400 == 0)
        islp = 1;
    y--;
    lp = y/4 - y/100 + y/400;
    return y*365 + lp + mm[m] + d + (m > 2 ? islp : 0);
}
int main() {
    int t, base = cntDay(1981,7,1);
    int y, m, d;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d %d", &y, &m, &d);
        int tmp = cntDay(y, m, d);
        printf("%d\n", (abs(base - tmp)+3)%7+1);
    }
    return 0;
}
