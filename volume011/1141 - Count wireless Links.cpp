#include <stdio.h> 
#include <math.h>
#include <algorithm>
#include <set>
#include <map>
#include <queue>
#include <vector>
#include <string>
#include <iostream>
#include <assert.h>
#include <string.h>
#include <list>
using namespace std;

#define eps 1e-8
#define MAXV 524288
namespace {
#define TYPE_P int64_t
	struct Point {
	    TYPE_P x, y;
	    Point(TYPE_P a = 0, TYPE_P b = 0):
	    x(a), y(b) {}
	    Point operator-(const Point &a) const {
	        return Point(x - a.x, y - a.y);
	    }
	    Point operator+(const Point &a) const {
	        return Point(x + a.x, y + a.y);
	    }
	    Point operator*(const TYPE_P a) const {
	        return Point(x * a, y * a);
	    }
	    bool operator<(const Point &a) const {
	        if (fabs(x - a.x) > eps)	return x < a.x;
	        if (fabs(y - a.y) > eps)	return y < a.y;
	        return false;
	    }
	    bool operator==(const Point &a) const {
	        return fabs(x - a.x) < eps && fabs(y - a.y) < eps;
	    }
	    bool operator!=(const Point &a) const {
	        return !(fabs(x - a.x) < eps && fabs(y - a.y) < eps);
	    }
	    inline double dist(Point b) const {
	        return hypot(x - b.x, y - b.y);
	    }
	    inline TYPE_P dist2(Point b) const {
	        return (x - b.x) * (x - b.x) + (y - b.y) * (y - b.y);
	    }
	};
}

inline int readchar() {
    const int N = 1048576;
    static char buf[N];
    static char *p = buf, *end = buf;
    if (p == end) {
        if((end = buf + fread(buf, 1, N, stdin)) == buf) return EOF;
        p = buf;
    }
    return *p++;
}
inline int ReadInt(int *x) {
    static char c, neg;
    while ((c = readchar()) < '-')	{ if(c == EOF) return 0;}
    neg = (c == '-') ? -1 : 1;
    *x = (neg == 1) ? c-'0' : 0;
    while ((c = readchar()) >= '0')
        *x = (*x << 3) + (*x << 1) + c-'0';
    *x *= neg;
    return 1;
}

int main() {
	int L, H, R, N;
	static Point p[MAXV];
//	while (scanf("%d %d %d %d", &L, &H, &R, &N) == 4) {
	while (ReadInt(&L)) {
		ReadInt(&H), ReadInt(&R), ReadInt(&N);
		map<pair<int, int>, vector<int>> grid;
		int64_t r2 = (int64_t) R*R;
		
		const int dx[] = {0, 0, 0, 1, 1, 1, -1, -1, -1};
		const int dy[] = {0, 1, -1, -1, 0, 1, -1, 0, 1};
		int ret = 0;
		for (int i = 0; i < N; i++) {
			int x, y;
			ReadInt(&x), ReadInt(&y);
//			scanf("%d %d", &x, &y);
			p[i] = Point(x, y);
			int gx = x/R, gy = y/R, adj = 0;
			for (int j = 0; j < 9; j++) {
				int tx = gx+dx[j];
				int ty = gy+dy[j];
				auto it = grid.find({tx, ty});
				if (it != grid.end()) {
					for (auto v : it->second) {
						if (p[i].dist2(p[v]) < r2)
							adj++;
					}
					if (adj >= 31)
						break;
				}
			}
			ret += adj;
			grid[{gx, gy}].push_back(i);
		}
		printf("%d\n", ret);
	}
	return 0;
}
/*
10  10  5  3
0  0
4  0
0  5

30  20  11  6
0  0
0  10
10  0
10  10
20  0
20  10
*/
