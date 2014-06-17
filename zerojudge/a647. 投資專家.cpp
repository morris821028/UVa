#include <stdio.h>
#include <stdlib.h>
int main() {
    int t, a, b;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &a, &b);
        int n = (b-a)*10000/a;
        int m = (b-a)*100000/a%10;
        int tn = n;
        if(abs(m) > 4)   n = n + (n < 0 ? -1 : 1);
        printf("%s%d.%02d%% ", n < 0 ? abs(n/100) < 10 ? " -" : "-" : abs(n/100) < 10 ? "  ": " ", abs(n)/100, abs(n%100));
        if(tn <= -700 || tn >= 1000) {
            puts("dispose");
        } else {
            puts("keep");
        }
    }
    return 0;
}
