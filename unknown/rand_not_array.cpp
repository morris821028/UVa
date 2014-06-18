#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
double C(int n, int m) {
    int i;
    double sum = 0;
    for(i = m+1; i <= n; i++)
        sum += log10(i);
    for(i = 1; i <= n-m; i++)
        sum -= log10(i);
    return pow(10, sum);
}
double randDouble() {
    char buf[50];
    double p;
    sprintf(buf, "0.%03d", rand()%1000);
    sscanf(buf, "%lf", &p);
    return p;
}
int main() {
    srand ( time(NULL));
    int i, j, c = 10;
    for(i = 1; i <= 102 && c; i++) {
        double den, num;
        den = C(102-i+1, c);
        num = C(102-i, c-1);
        double p = (double)num/den;
        printf("%lf\n", p);
        double q = randDouble();
        if(q <= p || p > 0.99) {
            c--;
            printf("%d\n", i);
        }
    }
    return 0;
}

