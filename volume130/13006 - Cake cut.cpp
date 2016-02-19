#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <set>
#include <limits.h>
#include <algorithm>
using namespace std;

struct Pt {
    long long x, y;
    Pt(long long a = 0, long long b = 0):
    x(a), y(b) {}
    Pt operator-(const Pt &a) const {
        return Pt(x - a.x, y - a.y);
    }
    Pt operator+(const Pt &a) const {
        return Pt(x + a.x, y + a.y);
    }
    Pt operator*(const double a) const {
        return Pt(x * a, y * a);
    }
};
long long cross(Pt o, Pt a, Pt b) {
    return (a.x-o.x)*(b.y-o.y)-(a.y-o.y)*(b.x-o.x);
}
long long area2(Pt o, Pt a, Pt b) {
    return llabs(cross(o, a, b));
}
const int MAXN = 262144;
Pt P[MAXN];
int main() {
    int N;
    while (scanf("%d", &N) == 1) {
        for (int i = 0; i < N; i++) {
            scanf("%lld %lld", &P[i].x, &P[i].y);
            P[i+N] = P[i];
        }
        
        long long area = 0;
        for (int i = 2; i < N; i++)
            area += area2(P[0], P[i-1], P[i]);
        
        long long tmp = 0;
        pair<long long, long long> ret(0, 0);
        tmp += P[0].x * P[1].y - P[0].y * P[1].x;
        tmp += P[1].x * P[2].y - P[1].y * P[2].x;
        for (int i = 0, j = 2; i < N; i++) {
            while (1) {
                long long test = tmp + (P[j].x * P[i].y - P[j].y * P[i].x);
                if (llabs(test)*2 >= area)
                    break;
                tmp += P[j].x * P[j+1].y - P[j].y * P[j+1].x;
                j++;
            }
            long long t1, t2, p1, p2;
            t1 = llabs(tmp + (P[j].x * P[i].y - P[j].y * P[i].x));
            t2 = area - t1;
            p1 = llabs(tmp - (P[j-1].x * P[j].y - P[j-1].y * P[j].x)
                           + (P[j-1].x * P[i].y - P[j-1].y * P[i].x));
            p2 = area - p1;
            if (t1 < t2)    swap(t1, t2);
            if (p1 < p2)    swap(p1, p2);
            if (t1 > p1)    t1 = p1, t2 = p2;
            ret = max(ret, make_pair(t1, t2));
            tmp -= P[i].x * P[i+1].y - P[i].y * P[i+1].x;
        }
        printf("%lld %lld\n", ret.first, ret.second);
    }
    return 0;
}

