#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;

class IMAGE {
public:
    struct Pixel {
        int r, g, b;
        Pixel(int x = 0, int y = 0, int z = 0):
        r(x), g(y), b(z) {}
        void read() {
            scanf("%d %d %d", &r, &g, &b);
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
        Pixel operator/(const double x) const {
            return Pixel(r/x, g/x, b/x);
        }
        bool operator==(const Pixel &x) const {
            return r == x.r && g == x.g && b == x.b;
        }
        void print() {
            printf("%d %d %d", r, g, b);
        }
        int length() {
            return abs(r) + abs(g) + abs(b);
        }
        int dist(Pixel x) {
            return abs((r + g + b) - (x.r + x.g + x.b));
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
    void gray(int threshold) {
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                if (data[i][j].length() >= threshold*3)
                    data[i][j] = Pixel(255, 255, 255);
                else
                    data[i][j] = Pixel(0, 0, 0);
            }
        }
    }
} image;
int main() {
    int T;
    scanf("%d", &T);
    image.read();
    image.gray(T);
    image.print();
    return 0;
}
