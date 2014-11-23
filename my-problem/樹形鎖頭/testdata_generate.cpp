#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
using namespace std;
double random() {
	int r = rand();
	return (double) r / RAND_MAX;
}
main() {
	int n, m, t, a, b, c, tmp;
	int x, y, z, i, j, k, l, p, q;
	srand ( time(NULL));
	freopen("in.txt", "w+t", stdout);

	int T = 2;
	while(T--) {
		n = 10000, m = 10000;
		printf("%d %d\n", n, m);
		for (int i = 1; i < n; i++)
			printf("%d %d\n", rand()%i, i);
		for (int i = 0; i < m; i++)
			printf("%d %d %d\n", rand()%n, rand()%n, rand()%32765 + 1);
		puts("");
	}
	return 0;
}
