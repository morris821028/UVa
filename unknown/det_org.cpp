#include <stdio.h>
#include <algorithm>
#define M(x,i,j) *(x->v + (i)*(x->col) + (j))
#define mod 100000007LL
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
void freeMatrix(MATRIX x) {
    delete x->v;
    delete x;
}
long long det(MATRIX x) {
    int row, col, i, j, k;
    row = x->row, col = x->col;
    if(row == 2)
        return M(x,0,0)*M(x,1,1) - M(x,0,1)*M(x,1,0);
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
            val %= mod;
        }
    }
    freeMatrix(m);
    return val;
}
int main() {
    freopen("in.txt", "r+t", stdin);
	freopen("out.txt", "w+t", stdout);
    int n, i, j, k;
    while(scanf("%d", &n) == 1) {
        MATRIX m = new matrix(n, n);
        for(i = 0; i < n; i++) {
            for(j = 0; j < n; j++) {
                scanf("%lld", m->v + i*(m->col) + j);
            }
        }
        printf("%lld\n", (det(m)%mod+mod)%mod);
        freeMatrix(m);
    }
    return 0;
}
