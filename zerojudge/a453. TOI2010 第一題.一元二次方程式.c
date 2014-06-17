#include <stdio.h>
#include <math.h>
int main() {
    int t, a, b, c;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d %d", &a, &b, &c);
        int D = b*b - 4*a*c;
        if(D < 0 || (int)sqrt(D)*(int)sqrt(D) != D)
            puts("No");
        else
            puts("Yes");
    }
    return 0;
}
