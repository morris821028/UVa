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

int main() {
	int n, m, t, a, b, c, tmp;
	int x, y, z, i, j, k, l, p, q;
	srand ( time(NULL));
	freopen("in.txt", "w+t", stdout);

	int T = 1;
	while (T--) {
		n = 1000, m = 5;
		printf("%d %d\n", n, m);
		for (int i = 0; i < n; i++) { 
			for (int j = 0; j < m; j++)
				printf("%d ", rand()%10000);
			printf("%d\n", rand()%10000);
		} 
		q = 10000;
		printf("%d\n", q);
		for (int i = 0; i < q; i++) {
			int L[5] , R[5];
			for (int j = 0; j < m; j++) {
				L[j] = rand()%10000, R[j] = rand()%10000;
				if (L[j] > R[j])
					swap(L[j], R[j]);
			}
			for (int j = 0; j < m; j++)
				printf("%d%c", L[j], j == m -1 ? '\n' : ' ');
			for (int j = 0; j < m; j++)
				printf("%d%c", R[j], j == m -1 ? '\n' : ' ');
		}
		if (T)
			puts("");
	}
	return 0;
} 
