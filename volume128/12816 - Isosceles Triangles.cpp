#include <stdio.h>
#include <math.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <string.h>
#include <assert.h>
#include <map>
using namespace std;

struct Pt {
    long long x, y;
    Pt(long long a = 0, long long b = 0):
    x(a), y(b) {}
    bool operator<(const Pt &a) const {
        if(x != a.x)    return x < a.x;
        return y < a.y;
    }
    Pt operator-(const Pt &a) const {
        Pt ret;
        ret.x = x - a.x;
        ret.y = y - a.y;
        return ret;
    }
};
long long dist(Pt a, Pt b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}
long long cross(Pt o, Pt a, Pt b) {
    return (a.x-o.x)*(b.y-o.y)-(a.y-o.y)*(b.x-o.x);
}
int main() {
    int n;
    Pt D[128];
    long long x, y;
    while (scanf("%d", &n) == 1) {
        for (int i = 0; i < n; i++)
            scanf("%lld %lld", &x, &y), D[i] = Pt(x, y);
        long long ret = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                for (int k = j + 1; k < n; k++) {
                    long long d[3] = {dist(D[i], D[j]), dist(D[j], D[k]), dist(D[k], D[i])};
                    sort(d, d + 3);
                    if (cross(D[i], D[j], D[k]) != 0)
                    if ((d[0] == d[1] && d[1] != d[2]) || (d[1] == d[2] && d[0] != d[1]))
                        ret++;
                }
            }
        }
        printf("%lld\n", ret);
    }
    return 0;
}
/*
 6
 -4 1
 -3 3
 -2 1
 -2 0
 -1 1
 -1 -1
 3
 -4 1
 -2 1
 -1 1
 */