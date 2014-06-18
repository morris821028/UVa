#include <stdio.h>
#include <algorithm>
#define M(x,i,j) *(x->v + (i)*(x->col) + (j))
using namespace std;
struct matrix {
    int row, col;
    long long* v;
    matrix(int x, int y) {
        row = x, col = y;
        v = new long long[x * y];
    }
};
typedef struct matrix *MATRIX;
long long gcd(long long a, long long b) {
    if(b == 0)  return a;
    if(a < 0)   a *= -1;
    if(b < 0)   b *= -1;
    long long t;
    while(a%b)
        t = a, a = b, b = t%b;
    return b;
}
void freeMatrix(MATRIX x) {
    delete x->v;
    delete x;
}
long long det(MATRIX x) {
    int row, col, i, j, k, incnt = 0;
    row = x->row, col = x->col;
    if(row == 2)
        return M(x,0,0)*M(x,1,1) - M(x,0,1)*M(x,1,0);
    /*reduced row-echelon form*/
    long long div = 1;
    for(i = 0; i < row; i++) {
        int inch = i; /*interchange*/
        for(j = i; j < row; j++)
            if(M(x, j, i)) {
                inch = j;   break;
            }
        if(!M(x, inch, i))  continue;
        if(i != inch) {
            for(j = i, incnt++; j < col; j++)
                swap(M(x, i, j), M(x, inch, j));
        }
        long long g, a, b;
        for(j = 0; j < row; j++) {
            if(j == i || !M(x, j, i))  continue;
            g = gcd(M(x, i, i), M(x, j, i));
            g = M(x, i, i)/g*M(x, j, i);
            a = g/M(x, i, i);
            b = g/M(x, j, i);
            div *= b;
            for(k = 0; k < col; k++)
                M(x, j, k) = M(x, j, k)*b - M(x, i, k)*a;
        }
    }
    long long val = 0;
    MATRIX m = new matrix(row-1, row-1);
    for(i = 1; i < row; i++) {
        for(j = 1; j < row; j++) {
            M(m,i-1,j-1) = M(x,i,j);
        }
    }
    for(i = 0; i < row; i++) {
        if(i) {
            for(j = 1; j < row; j++)
                M(m,j-1,i-1) = M(x,j,i-1);
        }
        if(M(x, 0, i)) {
            val += ((i&1) ? -1 : 1)*det(m)*M(x,0,i);
        }
    }
    freeMatrix(m);
    return ((incnt&1) ? -1 : 1)*val/div;
}
int main() {
    int n, i, j, k;
    while(scanf("%d", &n) == 1) {
        MATRIX m = new matrix(n, n);
        for(i = 0; i < n; i++) {
            for(j = 0; j < n; j++) {
                scanf("%lld", m->v + i*(m->col) + j);
            }
        }
        printf("det(A) = %lld\n", det(m));
        freeMatrix(m);
    }
    return 0;
}
/*
2
1 2
3 4
4
2 -1 0 3
-1 2 1 0
1 0 2 -4
2 3 1 1
3
-9 -18 -27
6 -1 3
0 -5 -7
4
2 0 1 0
1 3 0 2
0 1 -2 1
4 0 1 1
4
2 0 0 0
4 -2 0 0
-5 6 1 0
1 5 3 3
5
-1 0 0 0 0
0 3 0 0 0
0 0 2 0 0
0 0 0 4 0
0 0 0 0 -2
5
2 0 1 3 -2
-2 1 3 2 -1
1 0 -1 2 3
3 -1 2 4 -3
1 1 3 2 0
*/
