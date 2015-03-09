#include <stdio.h> 
#include <math.h>
int main() {
	int N;
	while (scanf("%d", &N) == 1) {
		int n, u, s;
		int a = 0, a2 = 0, tot = 0;
		for (int i = 0; i < N; i++) {
			scanf("%d %d %d", &n, &u, &s);
			a += u * n;
			a2 += (s * s * n + n * u * u);
			tot += n;
		}
		double avg = (double)a / tot;
		double t = sqrt((double)(a2 - 2 * avg * a + avg * avg * tot)/tot);
		printf("%d %.2lf %.2lf\n", tot, avg, t);
	}
	return 0;
}
