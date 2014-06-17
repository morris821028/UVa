#include <stdio.h>
int cent(double cost, double p) {
    double a = p*100*cost;
    char s[100];
    int cc;
    sprintf(s, "%.lf", a);
    sscanf(s, "%d", cc);
    return cc;
}
int main() {
    double dist, cap, perG, costO;
    int n;
    while(scanf("%lf", &dist) == 1) {
        if(dist == -1)
            break;
        scanf("%lf %lf %lf", &cap, &perG, &costO);
        scanf("%d", &n);
        double tcap = cap, x[100], y[100];
        int cost = 0;
        x[0] = 0, y[0] = 0;
        x[n+1] = dist;
        for(i = 1; i <= n; i++)
            scanf("%lf %lf", &x[i], &y[i]);
        for(i = 0; i <= n; i++) {
            if(tcap*perG+x[i] < x[i+1]) {
                cost += cent(y[i], cap-tcap);
                tcap = cap;
                cost += 2;
            }
        }
    }
    return 0;
}
