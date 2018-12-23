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
	int n;
	while (scanf("%d", &n) == 1) {
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

		double ret = 0;
		int mxOD = 0;
		for (int i = 0; i < X.size(); i++)
			for (int j = 0; j < Y.size(); j++)
				mxOD = max(mxOD, g[i][j]);

		for (int i = 0; i < X.size(); i++) {
			for (int j = 0; j < Y.size(); j++) {
				if (g[i][j] == mxOD) {
					ret += (X[i]-X[i-1])*(Y[j]-Y[j-1]);
				}
			}
		}
		printf("%.2lf\n", ret);
	}
	return 0;
}
/*
3
-5.00 -2.00 -1.0 2.0
2.5 -1 -4.5 1.0
4 3 0 -4
*/
