#include <stdio.h> 
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
double distForAllPoints(double x, double y, 
						vector< pair<int, int> > &D) {
	double sum = 0;
	for(int i = D.size()-1; i >= 0; i--) {
		sum += hypot(D[i].first - x, D[i].second - y);
	}
	return sum;
}
double randDouble() {
	return (rand() % 32767) / 32767.0;
}
double annealing(vector< pair<int, int> > &D) {
#define S_MUL 0.6f
#define S_LEN 1000
#define T_CNT 10
#define E_CNT 10
	double step = S_LEN;
	double x[E_CNT], y[E_CNT], val[E_CNT];
	double Lx, Ly, Rx, Ry, tx, ty, tcost;
	Lx = Rx = D[0].first;
	Ly = Ry = D[0].second;
	for(int i = 0; i < D.size(); i++) {
		Lx = min(Lx, (double)D[i].first);
		Rx = max(Rx, (double)D[i].first);
		Ly = min(Ly, (double)D[i].second);
		Ry = max(Ry, (double)D[i].second);
	}
	for(int i = 0; i < E_CNT; i++) {
		x[i] = randDouble() * (Rx - Lx) + Lx;
		y[i] = randDouble() * (Ry - Ly) + Ly;
		val[i] = distForAllPoints(x[i], y[i], D);
	}
	while(step > 0.1) {
		for(int i = 0; i < E_CNT; i++) {
			for(int j = 0; j < T_CNT; j++) {
				tx = x[i] + randDouble() * 2 * step - step;
				ty = y[i] + randDouble() * 2 * step - step;
				tcost = distForAllPoints(tx, ty, D);
				if(tcost < val[i]) {
					val[i] = tcost, x[i] = tx, y[i] = ty;
				}
			}
		}
		step *= S_MUL;
	}
	double ret = val[0];
	for(int i = 0; i < E_CNT; i++) {
		ret = min(ret, val[i]);
	}
	printf("%.0lf\n", ret);
}
int main() {
	int testcase, N;
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d", &N);
		vector< pair<int, int> > D;
		int x, y;
		for(int i = 0; i < N; i++) {
			scanf("%d %d", &x, &y);
			D.push_back(make_pair(x, y));
		}
		annealing(D);
		if(testcase)
			puts("");
	}
	return 0;
}
