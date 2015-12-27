#include <stdio.h>
 
int main() {
    int x, n = 0;
    double sum = 0, rank = 0;
    while (scanf("%d", &x) == 1) {
        n++;
#ifdef HUNDRED
        printf("%d ", x), sum += x;
#endif
#ifdef APLUS
        if (x >= 90) {
            printf("A+ ");
            rank += 4.3, sum += 95;
        } else if (x >= 85) {
            printf("A ");
            rank += 4.0, sum += 87;
        } else if (x >= 80) {
            printf("A- ");
            rank += 3.7, sum += 82;
        } else if (x >= 77) {
            printf("B+ ");
            rank += 3.3, sum += 78;
        } else if (x >= 73) {
            printf("B ");
            rank += 3.0, sum += 75;
        } else if (x >= 70) {
            printf("B- ");
            rank += 2.7, sum += 70;
        } else if (x >= 67) {
            printf("C+ ");
            rank += 2.3, sum += 68;
        } else if (x >= 63) {
            printf("C ");
            rank += 2.0, sum += 65;
        } else if (x >= 60) {
            printf("C- ");
            rank += 1.7, sum += 60;
        } else {
            printf("F ");
            sum += 50;
        }
#endif
    }
#ifdef HUNDRED
    printf("%.1f\n", sum / n);
#endif
#ifdef APLUS
    printf("%.1f %.1f\n", rank / n, sum / n);
#endif
    return 0;
}


