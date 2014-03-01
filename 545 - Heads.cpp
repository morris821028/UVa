#include <stdio.h>
#include <math.h>
int main() {
    int t, n;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        int e = (int)floor(-n*log10(2));
        printf("2^%d = %.3lfE%d\n", -n, pow(10, -n*log10(2)-e), e);
    }
    return 0;
}
