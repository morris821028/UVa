#include <bits/stdc++.h>
using namespace std;

#define eps 1e-8

struct Pt {
    double x, y;
    Pt(double a = 0, double b = 0): x(a), y(b) {}
};

struct Rect {
    Pt s, e;
    Rect(Pt a = Pt(), Pt b = Pt()):s(a), e(b) {}
};

int g[205][205];
vector<double> X, Y;

int relabel_x(double x) {
	return upper_bound(X.begin(), X.end(), x) - X.begin();
}
int relabel_y(double y) {
	return upper_bound(Y.begin(), Y.end(), y) - Y.begin();
}
Rect relabel_rect(Rect rect) {
	rect.s.x = relabel_x(rect.s.x);
	rect.e.x = relabel_x(rect.e.x);
	rect.s.y = relabel_y(rect.s.y);
	rect.e.y = relabel_y(rect.e.y);
	return rect;
}


int main() {
	int testcase;
	int n, m;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		X.clear(), Y.clear();
		vector<Rect> rect(n);
		for (int i = 0; i < n; i++) {
			double xa, xb, ya, yb;
			scanf("%lf %lf %lf %lf", &xa, &ya, &xb, &yb);
			rect[i] = Rect(Pt(min(xa, xb), min(ya, yb)), Pt(max(xa, xb), max(ya, yb)));
			X.push_back(xa);
			X.push_back(xb);
			Y.push_back(ya);
			Y.push_back(yb);
		}

		sort(X.begin(), X.end());
		sort(Y.begin(), Y.end());
		X.resize(unique(X.begin(), X.end())-X.begin());
		Y.resize(unique(Y.begin(), Y.end())-Y.begin());

		memset(g, 0, sizeof(g));
		for (int i = 0; i < n; i++) {
			rect[i] = relabel_rect(rect[i]);
			for (int p = rect[i].s.x; p < rect[i].e.x; p++) {
				for (int q = rect[i].s.y; q < rect[i].e.y; q++) {
					g[p][q]++;
				}
			}
		}

//		for (int i = 0; i < X.size(); i++) {
//			for (int j = 0; j < Y.size(); j++) {
//				printf("%d ", g[i][j]);
//			}
//			puts("");
//		}
//		for (int i = 0; i < Y.size(); i++)
//			printf("%lf \n", Y[i]);
		scanf("%d", &m);
		for (int i = 0; i < m; i++) {
			double y;
			scanf("%lf", &y);
			int gy = relabel_y(y);
			if (gy == 0 || gy == Y.size()) {
				puts("0");
				continue;
			} else {
				int ret = 0, pos_l = 0, pos_r;
				for (int i = 0; i < X.size(); i++) {
					if (g[i][gy] > ret) {
						ret = g[i][gy], pos_l = i;
						while (i < X.size() && g[i][gy] == ret)
							i++;
						pos_r = i;
						i--;
					}
				}
				if (ret == 0)
					puts("0");
				else
					printf("%d %.2lf %.2lf\n", ret, X[pos_l-1], X[pos_r-1]);
			}
		}
		if (testcase)
			puts("");
	}
	return 0;
}
/*
1

3
-5.00 -2.00 -1.00 2.0
2.5 -1 -4.5 1.0
4 3 0 -4
4
-0.2
-4.50
-3.8
1.50

*/
