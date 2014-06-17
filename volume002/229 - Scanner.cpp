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
int main() {
    int n, m, i, j, k, l;
    int testcase;
    Frac mx[151][155];
    scanf("%d", &testcase);
    while(testcase--) {
        m = 0, n = 150;
        for(i = 0; i < 10; i++) {
            scanf("%d", &k);
            for(j = 0; j <= n; j++)
                mx[m][j].a = 0, mx[m][j].b = 1;
            for(j = i*15; j < i*15+15; j++)
                mx[m][j].a = 1;
            mx[m][n].a = k;
            m++;
        }
        for(i = 0; i < 10; i++) {
            scanf("%d", &k);
            for(j = 0; j <= n; j++)
                mx[m][j].a = 0, mx[m][j].b = 1;
            for(j = i, l = 0; j >= 0; j--, l++)
                mx[m][j*15+l].a = 1;
            mx[m][n].a = k;
            m++;
        }
        for(i = 0; i < 14; i++) {
            scanf("%d", &k);
            for(j = 0; j <= n; j++)
                mx[m][j].a = 0, mx[m][j].b = 1;
            for(j = 9, l = i+1; j >= 0 && l < 15; j--, l++)
                mx[m][j*15+l].a = 1;
            mx[m][n].a = k;
            m++;
        }
        for(i = 0; i < 15; i++) {
            scanf("%d", &k);
            for(j = 0; j <= n; j++)
                mx[m][j].a = 0, mx[m][j].b = 1;
            for(j = 0; j < 10; j++)
                mx[m][j*15+i].a = 1;
            mx[m][n].a = k;
            m++;
        }
        for(i = 0; i < 15; i++) {
            scanf("%d", &k);
            for(j = 0; j <= n; j++)
                mx[m][j].a = 0, mx[m][j].b = 1;
            for(j = 9, l = i; j >= 0 && l >= 0; j--, l--)
                mx[m][j*15+l].a = 1;
            mx[m][n].a = k;
            m++;
        }
        for(i = 0; i < 9; i++) {
            scanf("%d", &k);
            for(j = 0; j <= n; j++)
                mx[m][j].a = 0, mx[m][j].b = 1;
            for(j = 8-i, l = 14; j >= 0 && l >= 0; j--, l--)
                mx[m][j*15+l].a = 1;
            mx[m][n].a = k;
            m++;
        }
        Frac tmp, one(1,1);
        int idx = 0, ch;
        for(i = 0; i < m; i++) {
            while(idx < n) {
                ch = -1;
                for(j = i; j < m; j++)
                    if(mx[j][idx].a) {ch = j;break;}
                if(ch == -1) {idx++;continue;}
                if(i != ch)
                    for(j = idx; j <= n; j++)
                        swap(mx[ch][j], mx[i][j]);
                break;
            }
            if(idx >= n) break;
            tmp = one/mx[i][idx];
            for(j = idx; j <= n; j++)
                mx[i][j] = mx[i][j]*tmp;
            for(j = 0; j < m; j++) {
                if(i == j)  continue;
                tmp = mx[j][i]/mx[i][idx];
                for(k = idx; k <= n; k++)
                    mx[j][k] = mx[j][k] - tmp*mx[i][k];
            }
            idx++;
        }
        for(i = 0; i < m; i++, puts("")) {
            for(j = 0; j <= n; j++) {
                if(mx[i][j].b != 1)
                printf("%lld/%lld ", mx[i][j].a, mx[i][j].b);
                else
                printf("%lld ", mx[i][j].a);
            }
        }
        puts("------------");
    }
    return 0;
}
