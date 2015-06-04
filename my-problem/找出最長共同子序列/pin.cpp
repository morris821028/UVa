#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <set>
#include <iostream>
#include <algorithm>
using namespace std;
#define eps 1e-6
double random() {
	int r = rand();
	return (double) r / RAND_MAX;
}
int toChar(int x) {
	if (x < 10)
		return x + '0';
	return x - 10 + 'A';
}
main() {
	int n, m, t, a, b, c, tmp;
	int z, i, j, k, l, p, q;
	srand ( time(NULL));
	freopen("in.txt", "w+t", stdout);

	int T = 30;
	while(T--) {
		int n = 20, q = rand()%15+1;
		printf("%d\n", n);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < 5; j++)
				printf("%d ", rand()%15+1);
			puts("");
		} 
		printf("%d\n", q);
		for (int i = 0; i < q; i++) {
			printf("%d\n", rand()%3+1);
			for (int j = 0; j < 5; j++)
				printf("%d ", rand()%15+1);
			puts("");
		}
		puts("");
	}
	
	return 0;
}
