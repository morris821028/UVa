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

int main() {
//	sieve();
	srand (time(NULL));
	int testcase, n, m, x, y, a, b;
	freopen("in.txt", "w+t", stdout);
	testcase = 1; 
	while (testcase--) {
		n = 100000000, m = 100000;
		
		printf("%d %d\n", n, m);
		for (int i = 0; i < m; i++) {
			if (rand()%5) {
				int l, r;
				do {
					l = rand()*rand()%n+1, r = rand()*rand()%n+1;
					if (l > r)	swap(l, r);
					if (r - l > 0)
						break;
				} while (true);
				printf("0 %d %d\n", l, r);
			} else {
				int x = rand()*rand()%n+1;
				printf("1 %d\n", x);
			}
		}
		if (testcase)
			puts("");
	}	
	return 0;
}
