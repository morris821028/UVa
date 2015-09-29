#include <bits/stdc++.h>
using namespace std;
struct Pt {
	int x, y;
	Pt(int a = 0, int b = 0):
		x(a), y(b) {}
	Pt operator-(const Pt &a) const {
		return Pt(x-a.x, y-a.y);
	}
	bool operator<(const Pt &a) const {
		if (x != a.x)	return x < a.x;
		return y < a.y;
	}
};
int main() {
	int n, x, y;
	Pt P[4096], L[4096], R[4096];
	while (scanf("%d", &n) == 1) {
		for (int i = 0; i < n; i++)
			scanf("%d %d", &x, &y), P[i] = Pt(x, y);
		sort(P, P+n);
		
		int ret = 0;
		for (int i = 0; i < n; i++) {
			int l = 0, r = 0;
			for (int j = 0; j < n; j++) {
				if (P[i].x == P[j].x)	continue;
				if (P[i].y == P[j].y)	continue;
				if (P[j].x < P[i].x)	L[l++] = P[j]-P[i];
				else					R[r++] = P[j]-P[i];
			}
			int Ay, By;
			Ay = 0x3f3f3f3f, By = -0x3f3f3f3f;
			for (int i = 0; i < r; i++) {
				if (R[i].y > 0) {
					if (R[i].y < Ay)	Ay = R[i].y, ret++;
				} else {
					if (R[i].y > By)	By = R[i].y, ret++;
				}
			}
			Ay = 0x3f3f3f3f, By = -0x3f3f3f3f;
			for (int i = l-1; i >= 0; i--) {
				if (L[i].y > 0) {
					if (L[i].y < Ay)	Ay = L[i].y, ret++;
				} else {
					if (L[i].y > By)	By = L[i].y, ret++;
				}
			}
		}
		printf("%d\n", ret/2);
	}
	return 0;
}
