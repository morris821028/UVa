#include <stdio.h>
#include <math.h>

int x[1000001] = {1};
int main() {
    int i, a, b, c;
    for(i = 1; i <= 1000000; i++) {
        a = (int)(i-sqrt(i));
        b = (int)log(i);
        c = (int)(i*sin(i)*sin(i));
        x[i] = (x[a]+x[b]+x[c])%1000000;
    }
    while(scanf("%d", &i) == 1 && i >= 0)
        printf("%d\n", x[i]);
    return 0;
}
