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
		n = 50000, m = 50000;
		
		printf("%d %d\n", n, m);
		for (int i = 0; i < n; i++)
			printf("%d%c", rand()%n+1, i == n-1 ? '\n' : ' ');
		for (int i = 0; i < m; i++) {
			int L, R, K;
			L = rand()*rand()%n+1;
			R = rand()*rand()%n+1;
			K = rand()*rand()%n+1;
			if (L > R)	swap(L, R);
			printf("%d %d %d\n", L, R, K);
		}
		if (testcase)
			puts("");
	}	
	return 0;
}
