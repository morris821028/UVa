#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
class Frac {
    public:
        long long a, b;
        Frac() {
            a = 0, b = 1;
        }
        Frac(int x, int y) {
            a = x, b = y;
            reduce();
        }
        Frac operator+(const Frac &y) {
            long long ta, tb;
            tb = this->b/gcd(this->b, y.b)*y.b;
            ta = this->a*(tb/this->b) + y.a*(tb/y.b);
            Frac z(ta, tb);
            return z;
        }
        Frac operator-(const Frac &y) {
            long long ta, tb;
            tb = this->b/gcd(this->b, y.b)*y.b;
            ta = this->a*(tb/this->b) - y.a*(tb/y.b);
            Frac z(ta, tb);
            return z;
        }
        Frac operator*(const Frac &y) {
            long long tx, ty, tz, tw, g;
            tx = this->a, ty = y.b;
            g = gcd(tx, ty), tx /= g, ty /= g;
            tz = this->b, tw = y.a;
            g = gcd(tz, tw), tz /= g, tw /= g;
            Frac z(tx*tw, ty*tz);
            return z;
        }
        Frac operator/(const Frac &y) {
            long long tx, ty, tz, tw, g;
            tx = this->a, ty = y.a;
            g = gcd(tx, ty), tx /= g, ty /= g;
            tz = this->b, tw = y.b;
            g = gcd(tz, tw), tz /= g, tw /= g;
            Frac z(tx*tw, ty*tz);
            return z;
        }
    private:
        static long long gcd(long long x, long long y) {
            if(!y)  return x;
            if(x < 0)   x *= -1;
            if(y < 0)   y *= -1;
            long long t;
            while(x%y)
                t = x, x = y, y = t%y;
            return y;
        }
        void reduce() {
            long long g = gcd(a, b);
            a /= g, b /= g;
            if(b < 0)   a *= -1, b *= -1;
        }
};
ostream& operator<<(ostream& out, const Frac&x) {
    out << x.a;
    if(x.b != 1)
        out << '/' << x.b;
    return out;
}
int main() {
    int n, m, i, j, k, N;
    char NUM[100], first = 0;
    long long X, Y;
    Frac matrix[100][100];
    while(scanf("%d", &N) == 1 && N) {
        scanf("%d %d", &n, &m);
        for(i = 0; i < m; i++) {
            for(j = 0; j <= n; j++) {
                scanf("%s", NUM);
                if(sscanf(NUM, "%lld/%lld", &X, &Y) == 2) {
                    matrix[i][j].a = X;
                    matrix[i][j].b = Y;
                } else
                    sscanf(NUM, "%lld", &matrix[i][j].a), matrix[i][j].b = 1;
            }
        }
        Frac tmp, one(1,1);
        int idx = 0, rank = 0;
        for(i = 0; i < m; i++) {
            while(idx < n) {
                int ch = -1;
                for(j = i; j < m; j++)
                    if(matrix[j][idx].a) {
                        ch = j;
                        break;
                    }
                if(ch == -1) {
                    idx++;
                    continue;
                }
                if(i != ch)
                    for(j = idx; j <= n; j++)
                        swap(matrix[ch][j], matrix[i][j]);
                break;
            }
            if(idx >= n) break;
            tmp = one/matrix[i][idx];
            rank++;
            for(j = idx; j <= n; j++)
                matrix[i][j] = matrix[i][j]*tmp;
            for(j = 0; j < m; j++) {
                if(i == j)  continue;
                tmp = matrix[j][i]/matrix[i][idx];
                for(k = idx; k <= n; k++) {
                    matrix[j][k] = matrix[j][k] - tmp*matrix[i][k];
                }
            }
            idx++;
        }
        if(first)   puts("");
        first = 1;
        printf("Solution for Matrix System # %d\n", N);
        int sol = 0;
        for(i = 0; i < m; i++) {
            for(j = 0; j < n; j++) {
                if(matrix[i][j].a)
                    break;
            }
            if(j == n) {
                if(matrix[i][n].a == 0 && sol != 1)
                    sol = 0; // INFINITELY
                else
                    sol = 1; // No Solution.
            }
        }
        if(rank == n && sol == 0) {
            for(i = 0; i < n; i++) {
                printf("x[%d] = ", i+1);
                cout << matrix[i][n] << endl;
            }
            continue;
        }
        if(sol == 1)
            puts("No Solution.");
        else
            printf("Infinitely many solutions containing %d arbitrary constants.\n", n-rank);
    }
    return 0;
}
