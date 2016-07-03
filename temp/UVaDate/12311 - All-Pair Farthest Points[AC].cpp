#include <stdio.h>
#include <algorithm>
using namespace std;

struct Point {
    long long x, y;
    Point(long long a = 0, long long b = 0):
    x(a), y(b) {}
    Point operator-(const Point &a) const {
        return Point(x - a.x, y - a.y);
    }
    long long dist2(Point &a) {
        return (x - a.x) * (x - a.x) + (y - a.y) * (y - a.y);
    }
    void read() {
        scanf("%lld %lld", &x, &y);
    }
};
const int MAXN = 32767;
const int THRESHOLD = 4;
Point pt[MAXN];
int farth_idx[MAXN];
long long farth_dist[MAXN];
void updateFarth(int i, int r, long long dd) {
    if (dd > farth_dist[i] || (dd == farth_dist[i] && r < farth_idx[i])) {
        farth_idx[i] = r;
        farth_dist[i] = dd;
    }
}
int main() {
    int n;
    while (scanf("%d", &n) == 1 && n) {
        for (int i = 0; i < n; i++)
            pt[i].read(), farth_idx[i] = i, farth_dist[i] = 0;
        
        for (int i = 0, p = 0, q = 1; i < n; i++) {
            while (pt[i].dist2(pt[q]) > pt[i].dist2(pt[p])) {
                p++, q++;
                if (p == n) p = 0;
                if (q == n) q = 0;
            }
            updateFarth(i, p, pt[i].dist2(pt[p]));
            for (int j = 0, r; j < THRESHOLD; j++) {
                r = (p + j)%n;
                updateFarth(i, r, pt[i].dist2(pt[r]));
                r = ((p - j)%n + n)%n;
                updateFarth(i, r, pt[i].dist2(pt[r]));
            }
        }
        
        for (int i = n-1, p = n-1, q = n-2; i >= 0; i--) {
            while (pt[i].dist2(pt[q]) > pt[i].dist2(pt[p])) {
                p--, q--;
                if (p < 0) p = n-1;
                if (q < 0) q = n-1;
            }
            updateFarth(i, p, pt[i].dist2(pt[p]));
            for (int j = 0, r; j < THRESHOLD; j++) {
                r = (p + j)%n;
                updateFarth(i, r, pt[i].dist2(pt[r]));
                r = ((p - j)%n + n)%n;
                updateFarth(i, r, pt[i].dist2(pt[r]));
            }
        }
        
        for (int i = 0; i < n; i++)
            printf("%d\n", farth_idx[i]+1);
    }
    return 0;
}