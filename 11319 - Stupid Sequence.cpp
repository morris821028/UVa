#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <string.h>
using namespace std;
double mtx[1505][10];
double o[1505][10];
#define eps 1e-3
int main() {
    //freopen("in.txt", "r+t", stdin);
    int testcase;
    scanf("%d", &testcase);
    int i, j, k;
    while(testcase--) {
        for(i = 1; i <= 1500; i++) {
            scanf("%lf", &mtx[i][8]);
            mtx[i][1] = 1;
            mtx[i][2] = pow(i, 1), mtx[i][3] = pow(i, 2);
            mtx[i][4] = pow(i, 3), mtx[i][5] = pow(i, 4);
            mtx[i][6] = pow(i, 5), mtx[i][7] = pow(i, 6);
        }
        memcpy(o, mtx, sizeof(o));
        for(i = 1; i <= 8; i++) {
            k = i;
            for(j = i+1; j <= 1500; j++)
                if(fabs(mtx[k][i]) < fabs(mtx[j][i]))
                    k = j;
            if(fabs(mtx[k][i]) < eps)
                continue;
            if(k != i) {
                for(j = 1; j <= 7+1; j++)
                    swap(mtx[k][j], mtx[i][j]);
            }
            for(j = 1; j <= 1500; j++) {
                if(i == j)  continue;
                for(k = 7+1; k >= i; k--)
                    mtx[j][k] -= mtx[j][i]/mtx[i][i]*mtx[i][k];
            }
        }
        int nosol[10] = {};
        double sol[10] = {};
        for(i = 7; i >= 1; i--) {
            if(fabs(mtx[i][8]) > eps && fabs(mtx[i][i]) < eps)
                nosol[i] = 1;
            else {
                if(fabs(mtx[i][7+1]) < eps)
                    sol[i] = 0;
                else
                    sol[i] = mtx[i][7+1]/mtx[i][i];
            }
            for(j = i+1; j <= 7; j++) {
                if(fabs(mtx[i][j]) > eps && nosol[j])
                    nosol[i] = 1;
            }
        }
        int hasSol = 1;
        for(i = 1; i <= 7; i++) {
            hasSol &= !nosol[i];
            if(round(sol[i]) < 0 || round(sol[i]) > 1000)
                hasSol = 0;
            sol[i] = round(sol[i]);
        }
        if(hasSol) {
            for(i = 1; i <= 1500 && hasSol; i++) {
                double sum = 0;
                for(j = 1; j <= 7; j++)
                    sum += sol[j] * pow(i, j-1);
                if(fabs(sum-o[i][8]) > eps) {
                    hasSol = 0;
                }
            }
        }
        if(hasSol == 0) {
            puts("This is a smart sequence!");
        } else {
            for(i = 1; i <= 7; i++) {
                if(i != 1)  putchar(' ');
                printf("%.0lf", sol[i]);
            }
            puts("");
        }
    }
    return 0;
}
