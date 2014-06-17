// Wrong Answer
#include <stdio.h> 
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
double distForAllPoints(double x, double y, 
						vector< pair<double, double> > &D) {
	double sum = 0;
	for(int i = D.size()-1; i >= 0; i--) {
		sum += hypot(D[i].first - x, D[i].second - y);
	}
	return sum;
}
double randDouble() {
	return (rand() % 32767) / 32767.0;
}
double annealing(vector< pair<double, double> > &D) {
#define S_MUL 0.314f // step shrink
#define S_LEN 314    // step init
#define T_CNT 31     // round test
#define E_CNT 14     // sample count
	double step = S_LEN;
	double x[E_CNT], y[E_CNT], val[E_CNT];
	double Lx, Ly, Rx, Ry, tx, ty, tcost;
	Lx = Rx = D[0].first;
	Ly = Ry = D[0].second;
	for(int i = 0; i < D.size(); i++) {
		Lx = min(Lx, D[i].first);
		Rx = max(Rx, D[i].first);
		Ly = min(Ly, D[i].second);
		Ry = max(Ry, D[i].second);
	}
	for(int i = 0; i < E_CNT; i++) {
		x[i] = randDouble() * (Rx - Lx) + Lx;
		y[i] = randDouble() * (Ry - Ly) + Ly;
		val[i] = distForAllPoints(x[i], y[i], D);
	}
	double dx[] = {0, 0, 1, -1};
	double dy[] = {1, -1, 0, 0};
	while(step > 0.01) {
		for(int i = 0; i < E_CNT; i++) {
			for(int k = 0; k < T_CNT; k++)
			for(int j = 0; j < 4; j++) {
				tx = x[i] + dx[j] * step;
				ty = y[i] + dy[j] * step;
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
	printf("%.4lf\n", ret);
}
int main() {
	srand(514);
	while(true) {
		vector< pair<double, double> > D;
		double x, y;
		for(int i = 0; i < 4; i++) {
			scanf("%lf %lf", &x, &y);
			D.push_back(make_pair(x, y));
		}
		if(D[0].first < 0)	break;
		annealing(D);
	}
	return 0;
}
