#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <set>
#include <map>
#include <fstream>
#include <iostream>
#include <assert.h>
using namespace std;

double random() {
	return (double) rand() / RAND_MAX;
}
int main() {
//	sieve();
	srand (time(NULL));
	int testcase, n, m, x, y, a, b;
	freopen("in.txt", "w+t", stdout);
	testcase = 1; 
	while (testcase--) {
		n = 100000, m = 100000;
		printf("%d %d\n", n, m);
//		for (int i = 2; i <= n; i++) {
//			printf("%d %d %d\n", i, i-1, rand()%10000 + 1);
//		}
//		for (int i = n; i <= m; i++) {
//			do {
//				x = rand()%n + 1;
//				y = rand()%n + 1;
//			} while (x == y);
//			printf("%d %d %d\n", x, y, rand()%30000 + 1);
//		}
		for (int i = 1; i <= m; i++) {
			do {
				x = rand()%n + 1;
				y = rand()%n + 1;
			} while (x == y);
			printf("%d %d %d\n", x, y, rand()%20000 + 1);
		}
	}	
	return 0;
}
