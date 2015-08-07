#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
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
            assert(r < 256 && g < 256 && b < 256);
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
        int sum() {
            return r + g + b;
        }
        int length() {
            return abs(r) + abs(g) + abs(b);
        }
        int dist(Pixel x) {
            return abs((r + g + b) - (x.r + x.g + x.b));
        }
    };
    int W, H;
    static const int MAXN = 512;
    Pixel data[MAXN][MAXN], tmp[MAXN][MAXN];
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
    void stat() {
        int cnt[4][512] = {};
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                cnt[0][data[i][j].r]++;
                cnt[1][data[i][j].g]++;
                cnt[2][data[i][j].b]++;
                cnt[3][(int)round(data[i][j].sum()/3.0)]++;
            }
        }
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 256; j++) {
                printf("%d%c", cnt[i][j], " \n"[j == 255]);
            }
        }
    }
} image;

int main() {
    image.read();
    image.stat();
    return 0;
}
