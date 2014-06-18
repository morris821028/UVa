#include <iostream>
#include <fstream>
#define LL long long
using namespace std;
class Frac {
    public:
        LL a, b;
        Frac() {
            a = 0, b = 1;
        }
        Frac(int x, int y) {
            a = x, b = y;
            reduce();
        }
        Frac operator+(const Frac &y) {
            LL ta, tb;
            tb = this->b/gcd(this->b, y.b)*y.b;
            ta = this->a*(tb/this->b) + y.a*(tb/y.b);
            Frac z(ta, tb);
            return z;
        }
        Frac operator-(const Frac &y) {
            LL ta, tb;
            tb = this->b/gcd(this->b, y.b)*y.b;
            ta = this->a*(tb/this->b) - y.a*(tb/y.b);
            Frac z(ta, tb);
            return z;
        }
        Frac operator*(const Frac &y) {
            LL tx, ty, tz, tw, g;
            tx = this->a, ty = y.b;
            g = gcd(tx, ty), tx /= g, ty /= g;
            tz = this->b, tw = y.a;
            g = gcd(tz, tw), tz /= g, tw /= g;
            Frac z(tx*tw, ty*tz);
            return z;
        }
        Frac operator/(const Frac &y) {
            LL tx, ty, tz, tw, g;
            tx = this->a, ty = y.a;
            g = gcd(tx, ty), tx /= g, ty /= g;
            tz = this->b, tw = y.b;
            g = gcd(tz, tw), tz /= g, tw /= g;
            Frac z(tx*tw, ty*tz);
            return z;
        }
    private:
        static LL gcd(LL x, LL y) {
            if(!y)  return x;
            if(x < 0)   x *= -1;
            if(y < 0)   y *= -1;
            LL t;
            while(x%y)
                t = x, x = y, y = t%y;
            return y;
        }
        void reduce() {
            LL g = gcd(a, b);
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
    int n, m, i, j, k;
    while(cin >> m) {
        n = 2*m;
        Frac matrix[m][n];
        for(i = 0; i < m; i++) {
            for(j = 0; j < n; j++) {
                if(j < m)
                    cin >> matrix[i][j].a;
                else
                    matrix[i][j].a = (j-m == i);
            }
        }
        Frac tmp, one(1,1), tmp2;
        for(i = 0; i < m; i++) {
            int ch = i;
            for(j = i; j < m; j++)
                if(matrix[j][i].a) {
                    ch = j;
                    break;
                }
            if(i != ch)
                for(j = i; j < n; j++)
                    tmp = matrix[i][j], matrix[i][j] = matrix[ch][j], matrix[ch][j] = tmp;
            if(matrix[i][i].a == 0)
                continue;
            tmp = one/matrix[i][i];
            for(j = i; j < n; j++)
                matrix[i][j] = matrix[i][j]*tmp;
            for(j = 0; j < m; j++) {
                if(i == j)  continue;
                tmp = matrix[j][i]/matrix[i][i];
                if(tmp.a == 0)  continue;
                for(k = i; k < n; k++) {
                    matrix[j][k] = matrix[j][k] - tmp*matrix[i][k];
                }
            }
        }
        for(i = 0; i < m; i++) {
            if(matrix[i][i].a != 1)
                break;
        }
        if(i != m) {
            puts("singular matrix\n");
            continue;
        }
        for(i = 0; i < m; i++) {
            for(j = m; j < n; j++) {
                cout << matrix[i][j] << ' ';
            }
            cout << endl;
        }
        cout << endl;
    }
    return 0;
}
/*
3
3 5 -1
2 -1 3
4 2 3
2
1 0
0 0
2
0 0
0 1
3
1 2 3
4 5 6
7 8 9
5
1 3 0 -1 0
0 -2 4 -2 0
3 11 -4 -1 0
2 5 3 -4 0
1 2 3 4 7
3
2 8 4
2 5 1
4 10 -1
3
1 2 3
8 10 12
7 8 9
3
1 2 3
4 5 6
7 8 9
3
2 1 -1
-3 -1 2
-2 1 2
3
2 4 -2
4 9 -3
-2 -3 7
3
2 4 -2
4 9 -3
-2 -3 7
3
2 3 -2
1 -2 3
4 -1 4
3
1 0 2
-3 4 6
-1 -2 3
*/
