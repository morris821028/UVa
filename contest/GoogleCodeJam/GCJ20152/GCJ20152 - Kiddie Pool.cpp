#include <bits/stdc++.h> 
using namespace std;

const int MAXN = 128;
const double eps = 1e-10;
double R[MAXN], C[MAXN], V, X;
int N;
vector< pair<double, double> > A;

int checkTime(double limitT) {
	double v, t, low_t, high_t;
	double mxV, teC;
	
	v = t = 0;
	for (int i = 0; i < N; i++) {
		mxV = A[i].second * limitT; // flow in limit time
		teC = A[i].first;
		
		mxV = min(mxV, V - v);
		t = (t * v + mxV * teC) / (v + mxV);
		v += mxV;
		if (v >= V - eps)
			break;
	}
	if (v < V - eps)
		return 0;
	low_t = t;
	
	v = t = 0;
	for (int i = N-1; i >= 0; i--) {
		mxV = A[i].second * limitT; // flow in limit time
		teC = A[i].first;
		
		mxV = min(mxV, V - v);
		t = (t * v + mxV * teC) / (v + mxV);
		v += mxV;
		if (v >= V - eps)
			break;
	}
	if (v < V - eps)
		return 0;
	high_t = t;
	return X >= low_t - eps && X <= high_t + eps;
}
int main() {
	int testcase, cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %lf %lf", &N, &V, &X);
		
		A.clear();
		for (int i = 0; i < N; i++) {
			scanf("%lf %lf", &R[i], &C[i]);
			A.push_back(make_pair(C[i], R[i]));
		}
		sort(A.begin(), A.end());
		
		double mxT, mnT;
		mnT = A[0].first, mxT = A[N-1].first;
		
		printf("Case #%d: ", ++cases);
		if (X < mnT - eps || X > mxT + eps) {
			puts("IMPOSSIBLE");
		} else {
			double l = 0, r = 1e+9, mid; // MAXV / MINR = 10000.0 / 0.0001 
			double ret = 0;
			for (int it = 0; it < 256; it++) {
				mid = (l + r)/2;
				if (checkTime(mid))
					r = mid, ret = mid;
				else
					l = mid;
			}
			printf("%.8lf\n", ret);
		}
	}
	return 0;
}
