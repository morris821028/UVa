#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <vector>
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
            printf("%3d", length());
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
    inline Pixel getPixel(int x, int y) {
        if (x >= 0 && y >= 0 && x < H && y < W)
            return data[x][y];
        if (y < 0)  return data[min(max(x, 0), H-1)][0];
        if (y >= W) return data[min(max(x, 0), H-1)][W-1];
        if (x < 0)  return data[0][min(max(y, 0), W-1)];
        if (x >= H) return data[H-1][min(max(y, 0), W-1)];
        return Pixel(0, 0, 0);
    }
    void sobel(int i, int j, int &gx, int &gy) {
        static int dx[] = {-1, -1, -1, 0, 0, 0, 1, 1, 1};
        static int dy[] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};
        static int yw[] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
        static int xw[] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};
        Pixel Dx(0, 0, 0), Dy(0, 0, 0);
        for (int k = 0; k < 9; k++) {
            if (xw[k])
                Dx = Dx + getPixel(i+dx[k], j+dy[k]) * xw[k];
            if (yw[k])
                Dy = Dy + getPixel(i+dx[k], j+dy[k]) * yw[k];
        }
        gx = Dx.sum(), gy = Dy.sum();
    }
    int used[MAXN][MAXN];
    int gx[MAXN][MAXN], gy[MAXN][MAXN];
    double gxy[MAXN][MAXN];
    int isValid(int x, int y) {
        return x >= 0 && y >= 0 && x < H && y < W;
    }
    int hough_circle() {
        int mxb = INT_MIN, mnb = INT_MAX;
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                int b = data[i][j].length();
                mxb = max(mxb, b), mnb = min(mnb, b);
            }
        }
        if (mxb - mnb < 300)
            return 0;
        int threshold = 250;
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                if (data[i][j].length() >= threshold)
                    data[i][j] = Pixel(1, 1, 1);
                else
                    data[i][j] = Pixel(0, 0, 0);
            }
        }
        
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                sobel(i, j, gx[i][j], gy[i][j]), gxy[i][j] = hypot(gx[i][j], gy[i][j]);
            }
        }
        
        int ret = 0;
        for (double r = 4; r <= min(H, W)/2; r += 1) {
            for (int i = 0; i < H; i++)
                for (int j = 0; j < W; j++)
                    used[i][j] = 0;
            for (int i = 0; i < H; i++) {
                for (int j = 0; j < W; j++) {
                    if (gxy[i][j] > 4) {
                        int xc, yc;
                        xc = round(i - r * (gx[i][j] / gxy[i][j]));
                        yc = round(j - r * (gy[i][j] / gxy[i][j]));
                        if (isValid(xc, yc))
                            used[xc][yc]++;
                    }
                }
            }
            
            int coins = 0;
            const int C = 3;
            for (int i = 0; i < H; i++) {
                for (int j = 0; j < W; j++) {
                    if (used[i][j] < 3)
                        continue;
                    int sum = 0, mx = 0, has = 0;
                    for (int p = -C; p <= C; p++) {
                        for (int q = -C; q <= C; q++) {
                            if (isValid(i+p, j+q))
                                sum += used[i+p][j+q], mx = max(mx, used[i+p][j+q]), has += used[i+p][j+q] > 0;
                        }
                    }
                    if (sum > 56 && (has > 36 || mx > 4)) {
                        coins++;
                        int cx = i, cy = j;
                        for (int p = -r-1; p <= r+1; p++) {
                            for (int q = -r-1; q <= r+1; q++) {
                                if (isValid(cx+p, cy+q))
                                    used[cx+p][cy+q] = 0;
                            }
                        }
                    }
                }
            }
            if (coins < ret - 2)
                break;
            ret = max(ret, coins);
        }
        return ret;
    }
} image;
int main() {
    image.read();
    printf("%d\n", image.hough_circle());
    return 0;
}
