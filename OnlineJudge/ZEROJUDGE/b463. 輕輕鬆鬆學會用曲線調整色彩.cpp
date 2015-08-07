#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <vector>
#include <algorithm>
using namespace std;

class GAUSSIAN { // Gaussian Elimination
public:
    static const int MAXN = 16;
    double mtx[MAXN][MAXN+1], var[MAXN];
    int exist[MAXN], n;
    vector< pair<double, double> > A;
    double f(double x) {
        if (x < A.front().first)
            return A.front().second;
        if (x > A.back().first)
            return A.back().second;
        double y = 0;
        for (int i = 0; i < n; i++)
            y += var[i] * pow(x, i);
        return y;
    }
    void add(pair<double, double> a) {
        A.push_back(a);
        sort(A.begin(), A.end());
    }
    void compute(int n) {
        const double eps = 1e-12;
        this->n = n;
        for (int i = 0, c; i < n; i++) {
            c = i;
            for (int j = i; j < n; j++)
                if (fabs(mtx[c][i]) < fabs(mtx[j][i]))
                    c = j;
            if (fabs(mtx[c][i]) < eps)
                continue;
            if (c != i) {
                for (int j = 0; j <= n; j++)
                    swap(mtx[c][j], mtx[i][j]);
            }
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
};
class IMAGE {
public:
    struct Pixel {
        double r, g, b;
        Pixel(double x = 0, double y = 0, double z = 0):
        r(x), g(y), b(z) {}
        void read() {
            scanf("%lf %lf %lf", &r, &g, &b);
        }
        Pixel operator-(const Pixel &x) const {
            return Pixel(r-x.r, g-x.g, b-x.b);
        }
        Pixel operator+(const Pixel &x) const {
            return Pixel(r+x.r, g+x.g, b+x.b);
        }
        Pixel operator*(const double x) const {
            return Pixel(r*x, g*x, b*x);
        }
        Pixel operator*(const Pixel &x) const {
            return Pixel(r*x.r, g*x.g, b*x.b);
        }
        Pixel operator/(const double x) const {
            return Pixel(r/x, g/x, b/x);
        }
        bool operator==(const Pixel &x) const {
            return r == x.r && g == x.g && b == x.b;
        }
        void print() {
            printf("%d %d %d", (int)round(r), (int)round(g), (int)round(b));
        }
        void normal() {
            r = max(min(r, 255.0), 0.0);
            g = max(min(g, 255.0), 0.0);
            b = max(min(b, 255.0), 0.0);
        }
    };
    int W, H;
    static const int MAXN = 256;
    Pixel data[MAXN][MAXN];
    void read() {
        scanf("%d %d", &W, &H);
        for (int i = 0; i < H; i++)
            for (int j = 0; j < W; j++)
                data[i][j].read();
    }
    void print() {
        printf("%d %d\n", W, H);
        for (int i = 0; i < H; i++)
            for (int j = 0; j < W; j++)
                data[i][j].print(), printf("%c", j == W-1 ? '\n' : ' ');
    }
    void blind(GAUSSIAN func[]) {
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                data[i][j].r = func[0].f(data[i][j].r);
                data[i][j].g = func[1].f(data[i][j].g);
                data[i][j].b = func[2].f(data[i][j].b);
                data[i][j].normal();
            }
        }
    }
} image;

int main() {
    GAUSSIAN func[3];
    for (int i = 0; i < 3; i++) {
        int gn;
        double gx, gfx;
        scanf("%d", &gn);
        for (int j = 0; j < gn; j++) {
            scanf("%lf %lf", &gx, &gfx);
            for (int k = 0; k < gn; k++)
                func[i].mtx[j][k] = pow(gx, k);
            func[i].mtx[j][gn] = gfx;
            func[i].add({gx, gfx});
        }
        func[i].compute(gn);
    }
    image.read();
    image.blind(func);
    image.print();
    return 0;
}