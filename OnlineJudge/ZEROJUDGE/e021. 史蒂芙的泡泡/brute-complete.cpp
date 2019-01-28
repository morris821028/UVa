#include <bits/stdc++.h>
using namespace std;

const int MAXN = 131072;
struct Point {
	int x, y;
} p[MAXN];
vector<int> A;

double interpolate_x(double y, Point p1, Point p2)
{
    if (p1.y == p2.y) return p1.x;
    return p1.x + (double) (p2.x - p1.x) * (y - p1.y) / (p2.y - p1.y);
}

int inside(double tx, double ty) {
	int c = 0;
	if (A.size() <= 1)
		return 0;
	for (int i = A.size()-1, j = 0; j < A.size(); i = j++) {
		if ((p[A[i]].y > ty) != (p[A[j]].y > ty) &&
            tx < interpolate_x(ty, p[A[i]], p[A[j]]))
            c++;
	}
	return c&1;
}

int64_t area() {
    int64_t ans = 0;
    for (int i = A.size()-1, j = 0; j < A.size(); i = j++)
        ans += p[A[i]].x*p[A[j]].y - p[A[i]].y*p[A[j]].x;
    return ans;
}

int main() {
	int n, m;
	while (scanf("%d %d", &n, &m) == 2) {
		for (int i = 0; i < n; i++)
			scanf("%d %d", &p[i].x, &p[i].y);

		int cmd, x, pos;
		for (int i = 0; i < m; i++) {
			scanf("%d", &cmd);
			if (cmd == 1) {
				scanf("%d %d", &x, &pos);
				A.insert(A.begin()+pos, x);
			} else if (cmd == 2) {
				scanf("%d", &x);
				A.erase(A.begin()+x);
			} else {
				double px, py;
				scanf("%lf %lf", &px, &py);
				puts(inside(px, py) ? "1" : "0");
			}
//			printf("%lld\n", area());
//			printf("[");
//			for (auto t : A)
//				printf("%d ", t);
//			printf("]\n");
//
//			printf("Polygon(");
//			for (int i = 0; i < A.size(); i++) {
//				printf("(%d, %d)%c", p[A[i]].x, p[A[i]].y, ",)"[i==A.size()-1]);
//			}
//			puts("");
		}
	}
	return 0;
}
