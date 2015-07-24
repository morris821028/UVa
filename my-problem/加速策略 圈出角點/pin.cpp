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

char g[2048][2048];
int main() {
//	sieve();
	srand (time(NULL));
	int testcase, n, m, x, y, a, b;
	freopen("in.txt", "w+t", stdout);
	testcase = 10; 
	while (testcase--) {
		int n = 1024, m = 1024;
		printf("%d %d %d\n", n, m, rand());
		continue;
		for (int it = 0; it < 5; it++) {		
			int r1 = rand()%(n/3) - n/5, r2 = rand()%(m/3) - m/4;
			int r3 = rand()%n, r4 = rand()%m, r5 = rand()%50 + 10;
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < m; j++) {
					int x = rand()%100 < 50;
					if (abs(i*i - j + r1) < 30)
						x = 1;
					if (abs(i*i - j*j + r1) < 50)
						x = 1;
					if (abs(i*j - j*j + r2) < 50)
						x = 1;
					if (abs(i*i - i*j + r2) < 50)
						x = 1;
					if (abs(i - r4) + abs(j - r3) < r5)
						x = 1;
					if (x)
						g[i][j] = x;
				}
			}
		}
		for (int i = 0; i < n; i++, puts(""))
			for (int j = 0; j < m; j++)
				printf("%d", g[i][j]), g[i][j] = 0;
	}	
	return 0;
}
