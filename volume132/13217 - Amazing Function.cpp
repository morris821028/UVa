#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <string.h>

int main() {
    double f[10];
    double f0 = sqrt(2) + sqrt(3) + sqrt(6);
    for (int i = 0; i < 10; i++) {
        f[i] = f0;
        f0 = (f0*f0-5)/(2*f0+4);
    }
    char s[4096];
    while (scanf("%s", s) == 1) {
        int n = strlen(s), x;
        if (n < 8) {
            sscanf(s, "%d", &x);
            if (x < 3)
                printf("%.10lf\n", f[x]);
            else
                printf("%.10lf\n", f[4-x%2]);
        } else {
            char c = s[n-1]-'0';
            printf("%.10lf\n", f[4-c%2]);
        }
    }
    return 0;
}
