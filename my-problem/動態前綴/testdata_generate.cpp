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

	int T = 100;
	while (T--) {
		n = 1000, m = 10000;
		for (int i = 0; i < n; i++)
			printf("%c", rand()%2 + 'a');
		puts("");
		printf("%d\n", m);
		for (int i = 0; i < m; i++) {
			if (rand()%10000 < 5000)
				printf("Q %d %d\n", rand()%n, rand()%n);
			else
				printf("C %d %c\n", rand()%n, rand()%2 + 'a');
		}
	}
	return 0;
}
