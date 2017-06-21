#include <bits/stdc++.h>
using namespace std;
#define eps 0

struct Pt {
    int x, y;
    Pt(int a = 0, int b = 0):
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
    bool operator<(const Pt &a) const {
        if (abs(x - a.x) > eps)
            return x < a.x;
        if (abs(y - a.y) > eps)
            return y < a.y;
        return false;
    }
};
static inline int cross2(Pt a, Pt b) {
    return a.x * b.y - a.y * b.x;
}
static inline int dot2(Pt a, Pt b) {
    return a.x * b.x + a.y * b.y;
}
bool cmp(const Pt& p1, const Pt& p2) {
    if (p1.y == 0 && p2.y == 0 && p1.x * p2.x <= 0) return p1.x > p2.x;
    if (p1.y == 0 && p1.x >= 0 && p2.y != 0) return true;
    if (p2.y == 0 && p2.x >= 0 && p1.y != 0) return false;
    if (p1.y * p2.y < 0) return p1.y > p2.y;
    int c = cross2(p1, p2);
    return c > 0 || (c == 0 && abs(p1.x) < abs(p2.x));
}
const int MAXN = 262144;
int main() {
	int n;
	while (scanf("%d", &n) == 1) {
		int a, b, m = 0, same = 0;
		static Pt A[MAXN];
		scanf("%d %d", &a, &b);
		n--;
		for (int i = 0; i < n; i++) {
			int x, y;
			scanf("%d %d", &x, &y);
			if (x == a && y == b) {
				same++;
				continue;
			}
			if (x < a && y < b)
				continue;
			A[m++] = Pt(x-a, y-b);
		}
		sort(A, A+m, cmp);
		for (int i = 0; i < m; i++)
			A[i+m] = A[i];
		
		int mn = n+2, mx = 0;
		for (int i = 0, j = 0; i < m; i++) {
			while (i+1 < m && cross2(A[i], A[i+1]) == 0 && dot2(A[i], A[i+1]) >= 0)
				i++;
			j = max(j, i);
			while (j-i+1 < m && cross2(A[i], A[j+1]) > 0) {
				j++;
			}
			if (A[i].x >= 0 && A[i].y <= 0) {
				mn = min(mn, j-i);
			}
		}
		for (int i = 0, j = 0; i < m; i++) {
			j = max(j, i);
			while (j-i+1 < m && cross2(A[i], A[j+1]) >= 0)
				j++;
			if (A[i].x >= 0 && A[i].y <= 0) {
				mx = max(mx, j-i+1+same);
			}
		}
		{
			int t1 = 0, t2 = 0, t1sa = 0, t2sa = 0;
			for (int i = 0; i < m; i++) {
				if (A[i].x > 0)	
					t1++;
				else if (A[i].x == 0)
					t1sa++;
				if (A[i].y > 0)	
					t2++;
				else if (A[i].y == 0)
					t2sa++;
			}
			mn = min(mn, t1);
			mn = min(mn, t2);
			mx = max(mx, t1+t1sa+same);
			mx = max(mx, t2+t2sa+same);
		}
		printf("%d %d\n", mn+1, mx+1);
	}
	return 0;
}
