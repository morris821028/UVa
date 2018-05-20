#include <bits/stdc++.h> 
using namespace std;

const int MAXN = 131072;

struct Pt3D {
	int x, y, z;
	Pt3D(int x=0, int y=0, int z=0):
		x(x), y(y), z(z) {}
};

inline int readchar() {
    const int N = 1048576;
    static char buf[N];
    static char *p = buf, *end = buf;
    if(p == end) {
        if((end = buf + fread(buf, 1, N, stdin)) == buf) return EOF;
        p = buf;
    }
    return *p++;
}
inline int ReadInt(int *x) {
    static char c, neg;
    while((c = readchar()) < '-')    {if(c == EOF) return 0;}
    neg = (c == '-') ? -1 : 1;
    *x = (neg == 1) ? c-'0' : 0;
    while((c = readchar()) >= '0')
        *x = (*x << 3) + (*x << 1) + c-'0';
    *x *= neg;
    return 1;
}

int main() {
	int n, m;
	static Pt3D pts[MAXN];
//	while (scanf("%d %d", &n, &m) == 2 && n) {
	while (ReadInt(&n) == 1 && ReadInt(&m) == 1 && n) {
		for (int i = 0; i < n; i++) {
			int x, y, z;
//			scanf("%d %d %d", &x, &y, &z);
			ReadInt(&x), ReadInt(&y), ReadInt(&z);
			pts[i] = Pt3D(x, y, z);
		}

		sort(pts, pts+n, [](const Pt3D &a, const Pt3D &b) {
			if (a.x != b.x)
				return a.x > b.x;
			return a.z < b.z;
		});
	
		int64_t ret = (int64_t) m*m*m;
		int64_t sum = 0;
		// Total - OR Volume
		set<pair<int, int>> S;
		S.insert({0, m+1});
		S.insert({m+1, 0});
		for (int i = 0; i < n; ) {
			int r = pts[i].x, l;
			while (i < n && pts[i].x == r) {
				auto it = S.upper_bound({pts[i].y, pts[i].z});
				if (it->second <= pts[i].z) {
					auto jt = it;
					pair<int, int> r = *it, l, m;
					jt--;
					while (jt->second <= pts[i].z) {
						m = *jt;
						S.erase(jt--);
						l = *jt;
						sum -= (m.first - l.first)*(m.second - r.second);
					}
					S.insert({pts[i].y, pts[i].z});
					sum += (pts[i].y- jt->first)*(pts[i].z - r.second);
				}
				i++;
			}
			if (i < n)
				l = pts[i].x;
			else
				l = 0;
			ret -= sum*(r-l);
		}
		printf("%lld\n", ret);
	}
	return 0;
}
/*
3 10
2 8 5
6 3 5
1 3 9

1 3
2 2 2

1 10000
2 2 2
*/
