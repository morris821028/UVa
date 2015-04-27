#include <stdio.h>
#include <math.h>
#include <vector>
#include <string.h>
#include <algorithm>
using namespace std;

/*
 0 1 2
 3 x 4
 5 6 7
 */
int main() {
    double A[10];
    const int n = 8;
    while (true) {
        for (int i = 0; i < n; i++)
            scanf("%lf", &A[i]);
        if (A[0] == 0)
            break;
        sort(A, A+n);
        double ret = 1e+30;
        do {
            double v = 0, h = 0;
            v = A[0] + A[1] + A[2] - A[5] - A[6] - A[7];
            h = A[0] + A[3] + A[5] - A[2] - A[4] - A[7];
            ret = min(ret, v * v + h * h);
        } while (next_permutation(A, A+n));
        printf("%.3lf\n", sqrt(ret));
    }
    return 0;
}
/*
 1 2 3 4 5 6 7 8
 0 0 0 0 0 0 0 0
*/