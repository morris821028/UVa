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
char g[2048][2048];
int A[512][512];
int main() {
//	sieve();
	srand (time(NULL));
	int testcase, n, m, x, y, a, b;
	freopen("in.txt", "w+t", stdout);
	testcase = 1; 
	while (testcase--) {
		int n = 500, m = 500;
		int p = 200, q = 200;
		printf("%d %d %d %d\n", n, m, p, q);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				printf("%d%c", rand()%64, j == m-1 ? '\n' : ' ');
			}
		}
		for (int i = 0; i < p; i++) {
			for (int j = 0; j < q; j++) {
				printf("%d%c", rand()%32, j == q-1 ? '\n' : ' ');
			}
		}
	}	
//	while (testcase--) {
//		int n = 100, m = 100;
//		int p = rand()%(n-50) + 10, q = rand()%(m-50) + 10;
//		printf("%d %d %d %d\n", n, m, p, q);
//		for (int i = 0; i < n; i++) {
//			for (int j = 0; j < m; j++) {
//				int v = (int)floor((1+sin(i + random()) * cos(j) + random())/2.0 * 255);
//				v = max(min(v, 255), 0);
//				A[i][j] = v;
//				printf("%d%c", v, j == m-1 ? '\n' : ' ');
//			}
//		}
//		int lx = rand()%(n - p), ly = rand()%(m - q);
//		for (int i = 0; i < p; i++) {
//			for (int j = 0; j < q; j++) {
//				int v = A[lx+i][ly+j] + rand()%10 - 5;
//				v = max(min(v, 255), 0);
//				printf("%d%c", v, j == q-1 ? '\n' : ' ');
//			}
//		}
//	}	
	return 0;
}
