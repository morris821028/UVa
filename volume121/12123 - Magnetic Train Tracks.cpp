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
long long getObtuseTriangle(int st, Pt D[], int n) {
	static Pt A[4096];
	int m = 0;
	for (int i = 0; i < n; i++) {
		if (i == st)	continue;
		A[m++] = Pt(D[i].x - D[st].x, D[i].y - D[st].y);
	}
	sort(A, A + m);
	for (int i = 0; i < m; i++)
		A[i + m] = A[i], A[i+m].angle += 2 * pi;
	long long ret = 0; // acute and right triangle
	for (int i = 0, j = 1; i < m; i++) { // point(st, i, ?)
		while (A[j].angle - A[i].angle <= pi/2 - eps)	j++;
		ret += j - i - 1;
	}
	return C[m][2] - ret;
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
		long long obtuse = 0;// obtuse triangle
		for (int i = 0; i < n; i++)
			obtuse += getObtuseTriangle(i, D, n); // with i-th point.
		printf("Scenario %d:\n", ++cases);
		printf("There are %lld sites for making valid tracks\n", C[n][3] - obtuse);
	}
	return 0;
}
/*
6
26 23
51 94
103 110
164 107
116 67
73 16
2
1 1
2 2
0
*/
