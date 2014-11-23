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
int A[262144] = {};
main() {
	int n, m, t, a, b, c, tmp;
	int x, y, z, i, j, k, l, p, q;
	srand ( time(NULL));
	freopen("in.txt", "w+t", stdout);

	int T = 2;
	while(T--) {
		n = 131070;
		for (int i = 1; i < n; i++)
			A[i] = A[i-1] + rand()%10 + 1;
		int m = 32 * n;
		if (T == 0)	m = 3;
		for (int i = 0; i < m; i++) {
			x = rand()%n, y = rand()%n;
			swap(A[x], A[y]);
		}
		printf("%d\n", n);
		for (int i = 0; i < n; i++)
			printf("%d%c", A[i], i == n - 1 ? '\n' : ' ');
	}
	return 0;
}
