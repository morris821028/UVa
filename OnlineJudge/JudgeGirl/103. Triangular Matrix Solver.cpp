#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
// Gaussian Elimination
#define MAXN 16
double mtx[MAXN][MAXN+1], var[MAXN];
int exist[MAXN];
void swap(double *x, double *y) {double t; t = *x, *x = *y, *y = t;}
void compute(int n) {
    const double eps = 1e-12;
    for (int i = 0, c; i < n; i++) {
        c = i;
        for (int j = i; j < n; j++)
            if (fabs(mtx[c][i]) < fabs(mtx[j][i]))
                c = j;
        if (fabs(mtx[c][i]) < eps)
            continue;
        for (int j = 0; j <= n; j++)
            swap(&mtx[c][j], &mtx[i][j]);
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            for (int k = n; k >= i; k--) {
                mtx[j][k] -= mtx[j][i]/mtx[i][i]*mtx[i][k];
            }
        }
    }
    for (int i = 0; i < n; i++)
        exist[i] = 1;
    for (int i = n-1; i >= 0; i--) {
        if (fabs(mtx[i][i]) < eps) {
            exist[i] = 0;
            continue;
        }
        if (fabs(mtx[i][n]) < eps)
            var[i] = 0;
        else
            var[i] = mtx[i][n]/mtx[i][i];
        for (int j = i+1; j < n; j++)
            if (fabs(mtx[i][j]) > eps && exist[j])
                exist[i] = 0;
    }
}
int main() {
	int n;
	while (scanf("%d", &n) == 1) {
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				scanf("%lf", &mtx[i][j]);
		for (int i = 0; i < n; i++)
			scanf("%lf", &mtx[i][n]);
		compute(n);
		for (int i = 0; i < n; i++)
			printf("%.6lf\n", var[i]);
	}
	return 0;
}
