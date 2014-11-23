#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <queue>
#include <set>
#include <map> 
#include <functional>
#include <math.h>
#include <string.h>
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

	int T = 1;
	T = 5;
	while(T--) {
		n = 10000;
		printf("%d\n", n);
		for (int i = 1; i < n; i++) {
			printf("%d %d\n", max(rand()%i, i - rand()%5 - 1), i);
		}
		m = 32767;
		printf("%d\n", m);
		for (int i = 0; i < m; i++) {
			if (rand()%100 > 98)
				printf("M %d\n", rand()%n);
			else
				printf("S %d\n", rand()%n);
		}
		puts("");
	}
	T = 1;
	while(T--) {
		n = 30000;
		printf("%d\n", n);
		for (int i = 1; i < n; i++) {
			printf("%d %d\n", i-1, i);
		}
		m = 30000;
		printf("%d\n", m);
		for (int i = 0; i < m; i++) {
			if (rand()%100 > 95)
				printf("M %d\n", rand()%n);
			else
				printf("S %d\n", rand()%n);
		}
		puts("");
	}
	return 0;
}
