#include <bits/stdc++.h>
using namespace std;
const int MAXN = 512;
const double eps = 1e-12;
const double pi = acos(-1);
int s[MAXN], n;

/*
    __    ___
   /  \  /   | 
---    --    /
   \__/  \__/
*/

inline double cmpZero(double x) {
	if (fabs(x) < eps)
		return 0;
	return x < 0 ? -1 : 1;
}

pair<double, int> sumAngle(int l, int r, double c) {
	double sum = 0, mx = -1;
	int mxidx = -1;
	for (int i = l; i <= r; i++) {
		double theta = asin(s[i]/2.0/c)*2;
		sum += theta;
		if (theta > mx)
			mx = theta, mxidx = i;
	}
	if (cmpZero(sum-mx-pi) >= 0) {
		// in the center
		return {cmpZero(sum-2*pi) >= 0, -1};
	} else {
		// not in the center
		return {cmpZero(sum-2*mx) <= 0, mxidx};
	}
}

inline double heron(double a, double b, double c) {
	double s = (a+b+c)/2;
	return sqrt(s*(s-a)*(s-b)*(s-c));
}

pair<double, int> coCircular(int l, int r) {
	// case 1: center of circle in the polygon
	// case 2: cetner of circle not in the polygon
	double cl = 0, cr = 0, cm;
	for (int i = l; i <= r; i++) {
		cl = max(cl, s[i]/2.0);
		cr = cr + s[i];
	}
	cr = cr * pi;

	int mxidx = -1;
	for (int it = 0; it < 80; it++) {
		cm = (cl+cr)/2;
		auto ret = sumAngle(l, r, cm);
		mxidx = ret.second;
		if (ret.first)
			cl = cm;
		else
			cr = cm;
	}

	double area = 0;
	for (int i = l; i <= r; i++) {
		if (i == mxidx)
			area -= heron(s[i], cm, cm);
		else
			area += heron(s[i], cm, cm);
	}
	return {area, mxidx};
}

double group(int l, int r) {
	if (r-l < 2)
		return 0;
	int sum = s[l], mx = s[l], mxidx = l;
	for (int i = l+1; i <= r; i++) {
		sum += s[i];
		if (s[i] > mx)
			mx = s[i], mxidx = i;
	}
	if (mx*2 >= sum) {	// partition by maximum length
		return group(l, mxidx-1) + group(mxidx+1, r);
	} else {
		auto t = coCircular(l, r);	// 
		if (t.second == -1)	// if center of circle is in the polygon,
			return t.first;
		// otherwise, try to partition.
		mxidx = t.second;
		return max(group(l, mxidx-1) + group(mxidx+1, r), t.first);
	}
}

int main() {
	int cases = 0;
	while (scanf("%d", &n) == 1 && n) {
		for (int i = 0; i < n; i++)
			scanf("%d", &s[i]);
		double ret = group(0, n-1);
		printf("Case %d: %.10lf\n", ++cases, ret);
	}
	return 0;
}
/*
4
1 2 3 4
8
3 4 5 33 3 4 3 5
3
3 4 5
0
*/
