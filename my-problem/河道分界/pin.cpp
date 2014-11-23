#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
using namespace std;
double random() {
	int r = rand();
	return (double) r / RAND_MAX;
}
int x[100005] = {}, y[100005] = {}, used[100005] = {};
main() {
	int n, m, t, a, b, c, tmp;
	int z, i, j, k, l, p, q;
	srand ( time(NULL));
	freopen("in.txt", "w+t", stdout);

	int T = 1;
	while(T--) {
		n = 30000;
		x[0] = rand()%10000 - 5000;
		y[0] = rand()%10000 - 5000;
		for (int i = 1; i < n; i++) {
			x[i] = x[i-1] + rand()%5 + 1;
			y[i] = y[i-1] + rand()%5 + 1;
		}
		for (int i = 0; i < n; i++) {
			int u = rand()%n, v = rand()%n;
			swap(x[u], x[v]);
			swap(y[u], y[v]);
		}
		printf("%d\n", n);
		for (int i = 0; i < n; i++) {
			if (rand()%10 > 5) {
				int s;
				do {
					s = rand()%n;
					if (!used[s])	break;
				} while (true);
				printf("A %d %d\n", x[s], y[s]);
				used[s] = 1;
			} else {
				printf("Q %lf %lf\n", random() * 10000 - 5000, random());
			}
		}
	}
	return 0;
}
