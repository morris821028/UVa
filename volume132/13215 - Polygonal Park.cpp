#include <bits/stdc++.h>
using namespace std;

int main() {
	static const int MAXN = 4096;
	static char C[MAXN][2];
	static double K[MAXN];
	static const double sqrt3 = sqrt(3);
	int testcase, n;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		double area = 0;
		for (int i = 0; i < n; i++) {
			scanf("%s %lf", &C[i], &K[i]);
			if (C[i][0] == 'C' || C[i][0] == 'S')
				area += K[i]*K[i];
			else
				area += K[i]*K[i]*sqrt3/4.f;
		}
		
		double h, v;
		for (int i = 0; i < n; i++) {
			if (C[i][0] == 'C') {
				h = K[i];
				int j;
				for (j = i+1; j < n; j++) {
					h += K[j];
					if (C[j][0] == 'C')
						break;
				}
				v = K[j];
				for (j = j+1; j < n; j++) {
					v += K[j];
					if (C[j][0] == 'C')
						break;
				}
				break;
			}
		}
		printf("%.4lf\n", h*v - area);
	}
	return 0;
}

