#include <stdio.h>
#include <math.h>
#include <vector>
#include <algorithm>
using namespace std;
const double pi = acos(-1);
vector<pair<double, double> > getIntersection(double a, double b, double c, double R) {
	// ax + by = c, x^2 + y^2 = R^2;
	vector<pair<double, double> > ret;
	double ta, tb, tc;
	double x1, x2, y1, y2, sq;
	if(fabs(b) > 1e-8) {
		ta = 1 + a*a/(b*b);
		tb = - 2*a*c/(b*b);
		tc = c*c/(b*b) - R*R;
		sq = tb*tb - 4*ta*tc;
		if(sq < 0)
			return ret;
		sq = sqrt(sq);
		x1 = (-tb + sq)/(2 * ta);
		x2 = (-tb - sq)/(2 * ta);
		if(fabs(x1 - x2) < 1e-8)
			goto same_x;
		y1 = (c - a * x1)/b;
		y2 = (c - a * x2)/b;
		ret.push_back(make_pair(x1, y1));
		ret.push_back(make_pair(x2, y2));
	} else {
		x1 = x2 = c / a;
		same_x:
		sq = R*R - x1*x1;
		if(sq < 0)
			return ret;
		sq = sqrt(sq);
		y1 = sq, y2 = -sq;		
		if(fabs(sq) > 1e-8)
			ret.push_back(make_pair(x1, y1));
		ret.push_back(make_pair(x2, y2));
	}
	return ret;
}
vector<pair<double, double> > THETA;
void getInterval(double x1, double y1, double x2, double y2,
	vector<pair<double, double> > I) {
	if(I.size() != 2)	return ;
	double vx, vy, l = 0, r = 1, tl, tr;
	vx = x2 - x1;
	vy = y2 - y1;
	tl = (I[0].first - x1) / vx;
	tr = (I[1].first - x1) / vx;
	if(tl > tr)	swap(tl, tr);
	l = max(l, tl), r = min(r, tr);
	if(l > r)	return ;
	x2 = x1 + vx * l;
	y2 = y1 + vy * l;
	tl = atan2(y2, x2);
	x2 = x1 + vx * r;
	y2 = y1 + vy * r;
	tr = atan2(y2, x2);
	if(tl > tr)	swap(tl, tr);
	if(tr - tl >= pi) {
		THETA.push_back(make_pair(-pi, tl));
		THETA.push_back(make_pair(tr, pi));
	} else {
		THETA.push_back(make_pair(tl, tr));
	}
	return ;
}
int main() {
	int testcase, cases = 0;
	int N, R; 
	int i, j, k;
	int x1, x2, y1, y2;
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d %d", &N, &R);
		THETA.clear();
		for(i = 0; i < N; i++) {
			scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
			double a, b, c;
			a = y2 - y1;
			b = x1 - x2;
			c = a * x1 + b * y1;
			vector<pair<double, double> > r = getIntersection(a, b, c, R);
			getInterval(x1, y1, x2, y2, r);
		}
		sort(THETA.begin(), THETA.end());
		double cover = 0;
		for(i = 0; i < THETA.size(); ) {
			double l = THETA[i].first, r = THETA[i].second;
			i++;
			while(i < THETA.size() && THETA[i].first < r) {
				r = max(r, THETA[i].second);
				i++;
			}
			cover += r - l;
		}
		printf("Case %d: %.2lf%%\n", ++cases, (2*pi - cover)*100 / (2*pi));
	}
	return 0;
}
/*
1
5 10
-5 4 -7 -9
5 -2 -5 7
4 -6 2 -10
9 -3 3 -8
-4 -8 5 3

2
1 10
2 0 0 2
0 5
*/
