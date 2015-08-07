#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <vector>
#include <algorithm>
using namespace std;

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
    void blind(Pixel a, Pixel b) {
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                data[i][j] = a * data[i][j] + b;
                data[i][j].normal();
            }
        }
    }
} image;

int main() {
    double a[6];
    for (int i = 0; i < 6; i++)
        scanf("%lf", &a[i]);
    IMAGE::Pixel arg[] = {IMAGE::Pixel(a[0], a[2], a[4]), IMAGE::Pixel(a[1], a[3], a[5])};
    image.read();
    image.blind(arg[0], arg[1]);
    image.print();
    return 0;
}