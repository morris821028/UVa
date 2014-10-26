#include <stdio.h>
#include <stdlib.h>

int main() {
    double R;
    int N;
    char cmd[6];
    while (scanf("%lf", &R) == 1) {
        scanf("%d", &N);
        double sumr = 1, sump = 1, p;
        for (int i = 0; i < N; i++) {
            scanf("%s %lf", cmd, &p);
            if (cmd[0] == 'R')
                sumr *= p, sump *= 1 - p;
            else
                sumr *= 1 - p, sump *= p;
        }
        sumr *= R, sump *= 1 - R;
        printf("%lf %lf\n", sumr / (sumr + sump), sump / (sumr + sump));
    }
    return 0;
}