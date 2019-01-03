#include <bits/stdc++.h>
using namespace std;

// Perceptron Learning Algorithm, PLA, machine learning

struct Pt3D {
	double x, y, z;
	void read() {
		scanf("%lf %lf %lf", &x, &y, &z);
	}
	double& operator[](int i) {
		if (i == 0)	return x;
		if (i == 1)	return y;
		if (i == 2)	return z;
		assert(false);
	}
};

int classify(double f[], Pt3D &p) {
	return f[0]*p.x+f[1]*p.y+f[2]*p.z+f[3] > 0;
}

const double step = 0.5;

int train(double f[], Pt3D &p, int type) {
	int err = type - classify(f, p);
	f[0] += err * step * p[0];
	f[1] += err * step * p[1];
	f[2] += err * step * p[2];
	f[3] += err * step;
	return err;
}

int main() {
	int n, m;
	Pt3D A[205], B[205];
	while (scanf("%d", &n) == 1 && n >= 0) {
		for (int i = 0; i < n; i++)
			A[i].read();
		scanf("%d", &m);
		for (int i = 0; i < m; i++)
			B[i].read();
			
		double f[4] = {0, 0, 0, 0};
		for (int it = 0; ; it++) {
			int err = 0;
			for (int i = 0; i < n; i++)
				err |= train(f, A[i], 0);
			for (int i = 0; i < m; i++)
				err |= train(f, B[i], 1);
			if (!err)
				break;
		}
		printf("%lf %lf %lf %lf\n", f[0], f[1], f[2], f[3]);
	}
	return 0;
}
/*
2
-93 48 -92
-62 12 -32
8
51 98 -61
-3 72 81
95 25 22
89 43 -99
100 -2 -96
-18 45 -63
36 -21 -8
71 -24 42
-1 -1
*/
