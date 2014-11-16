#include <stdio.h> 
#include <math.h>
#include <algorithm>
using namespace std;

#define eps 1e-9
const double pi = acos(-1);
struct Pt {
	double x, y;
	double angle;
	Pt(double a = 0, double b = 0):x(a), y(b) {
		angle = atan2(b, a);
	}
	bool operator<(const Pt &a) const {
		if (fabs(angle - a.angle) > eps)
			return angle < a.angle;
		return false;
	}
}; 
long long C[1300][1300] = {};
long long getContainTriangle(int st, Pt D[], int n) {
	static Pt A[4096];
	int m = 0;
	for (int i = 0; i < n; i++) {
		if (i == st)	continue;
		A[m++] = Pt(D[i].x - D[st].x, D[i].y - D[st].y);
	}
	sort(A, A + m);
	for (int i = 0; i < m; i++)
		A[i + m] = A[i], A[i+m].angle += 2 * pi;
	long long ret = 0;
	for (int i = 0, j = 1; i < m; i++) { // point(i, ?, ?)
		while (A[j].angle - A[i].angle <= pi - eps)	j++;
		ret += C[j - i - 1][2];
	}
	return C[m][3] - ret;
}
int main() {
	C[0][0] = 1;
	for (int i = 0; i < 1205; i++) {
		C[i][0] = 1;
		for (int j = 1; j <= i; j++)
			C[i][j] = C[i-1][j-1] + C[i-1][j];
	}
	int n, cases = 0;
	Pt D[1500];
	while (scanf("%d", &n) == 1 && n) {
		for (int i = 0; i < n; i++) 
			scanf("%lf %lf", &D[i].x, &D[i].y);
		long long contain = 0;// contain
		for (int i = 0; i < n; i++)
			contain += getContainTriangle(i, D, n); // with i-th point.
		printf("City %d: %.2lf\n", ++cases, (double)contain / C[n][3]);
	}
	return 0;
}
/*
5
29 84
81 81
28 36
60 40
85 38
5
0 0
10 0
0 10
10 10
6 7
0
*/
