#include <stdio.h>
#include <math.h>
#include <string.h>
#include <algorithm>
using namespace std;

const int MAXN = 64;
const int MAXM = 128;
const double eps = 1e-10, INF = 1e+30;
/*
	n: #variable
	m: #inequality constraint
	#inequality constraint format : \sum{a(j, i) xi} <= bj
	for all xi >= 0
 */
class Simplex {
public:
    int n, m;
    int N[MAXN], M[MAXM];
    double a[MAXM][MAXN], b[MAXM], c[MAXN];
    double xval[MAXN], z;
    void init(int n, int m) {
        memset(a, 0, sizeof(a));
        memset(b, 0, sizeof(b));
        memset(c, 0, sizeof(c));
        memset(xval, 0, sizeof(xval));
        z = 0;
        this->n = n + m;
        this->m = m;
        
        for (int i = 0; i < m; i++)
            a[i][n+i] = 1;
        for (int i = 0; i < n; i++)
            N[i] = i;
        for (int i = 0; i < m; i++)
            M[i] = n + i;
    }
    int cmpZero(double v) {
        if (fabs(v) < eps)	return 0;
        return v < 0 ? -1 : 1;
    }
    void compute_xval() {
        for (int i = 0; i < n - m; i++) {
            xval[i] = 0;
            for (int j = 0; j < m; j++) {
                if (M[j] == i)
                    xval[i] = b[j];
            }
        }
    }
    void print() {
        printf("c ");
        for (int i = 0; i < n; i++)
            printf("%6.3lf ", c[i]);
        printf("%6.3lf\n", z);
        
        for (int i = 0; i < m; i++) {
            printf("a ");
            for (int j = 0; j < n; j++)
                printf("%6.3lf ", a[i][j]);
            printf("%6.3lf\n", b[i]);
        }
        puts("--");
        
        compute_xval();
        printf("x ");
        for (int i = 0; i < n - m; i++)
            printf("%6.3lf ", xval[i]);
        puts("");
    }
    void pivot(int row, int col) {
        double e = a[row][col];
        // normalization
        b[row] /= e;
        for (int i = 0; i < n; i++)
            a[row][i] /= e;
        // gaussian elimination
        for (int i = 0; i < m; i++) {
            if (i == row)
                continue;
            double t = a[i][col];
            b[i] = b[i] - t * b[row];
            for (int j = 0; j < n; j++)
                a[i][j] = a[i][j] - t * a[row][j];
        }
        z -= b[row] * c[col];
        
        double t = c[col];
        for (int i = 0; i < n; i++)
            c[i] = c[i] - t * a[row][i];
        swap(N[col], M[row]);
//        print();
    }
    void simplex() {
        double mx;
        int select_col, select_row, mn_row;
        // climb
        do {
            mx = -INF, select_col = select_row = mn_row = -1;
            for (int i = 0; i < n; i++) {
                if (cmpZero(c[i]) > 0) {
                    double mn = INF;
                    // find minmum increase with inequality constraint
                    for (int j = 0; j < m; j++) {
                        if (cmpZero(a[j][i]) > 0) {
                            if (b[j] / a[j][i] < mn)
                                mn = b[j] / a[j][i], mn_row = j;
                        }
                    }
                    // find maxmum climb with axis
                    if (mx < mn * c[i]) {
                        mx = mn * c[i];
                        select_col = i, select_row = mn_row;
                    }
                }
            }
            if (select_col != -1)
                pivot(select_row, select_col);
        } while (select_col != -1);
        
        compute_xval();
    }
} g;

int main() {
    int n, m;
    while (scanf("%d %d", &n, &m) == 2) {
        g.init(n, m);
        
        for (int i = 0; i < n; i++)
            scanf("%lf", &g.c[i]);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++)
                scanf("%lf", &g.a[i][j]);
            scanf("%lf", &g.b[i]);
        }
        
        g.simplex();
        
//        for (int i = 0; i < n; i++) {
//            printf("x[%d] = %lf\n", i, g.xval[i]);
//        }
        printf("Nasa can spend %d taka.\n", (int) ceil(-g.z * m));
    }
    return 0;
}
/*
 Max x1 + 14*x2 + 6*x3
 s.t.
 x1 + x2 + x3 	<= 4
 x1              <= 2
 x3              <= 3
 3*x2   + x3     <= 6
 x1 , x2 , x3 , x4 , x5 , x6 , x7 >= 0
 
 3 4
 1 14 6
 1 1 1  4
 1 0 0  2
 0 0 1  3
 0 3 1  6
 
 2 2
 1 1
 2 1 12
 1 2 9
 
 2 2
 -1 -1
 2 1 12
 1 2 9
 
 3 3
 1 0.67 1.67
 1 2 1 430
 3 0 2 460
 1 4 0 420
 
 3 1
 30 10 20
 30 1 3 30
 
 3 3
 30 10 20
 30 1 3 30
 30 1 3 30
 30 1 3 30
 */
