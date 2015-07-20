#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <set>
#include <map>
#include <fstream>
#include <iostream>
using namespace std;

int main() {
//	sieve();
	srand (time(NULL));
	int testcase, n, m, x, y, a, b;
	freopen("in.txt", "w+t", stdout);
	testcase = 1; 
	while (testcase--) {
		int M = 30000, n = 100000;
		printf("%d\n\n", M);
		
		vector<int> A;
		for (int i = 0; i < 4*M; i++)
			A.push_back(rand()*rand());
		for (int i = 0; i < n; i++) {
			x = A[rand()*rand()%A.size()];
//			y = (rand() * rand())%1000000000;
			y = rand();
			if (rand()%100 < 20)
				printf("%d %d\n", 0, x);
			else
				printf("%d %d %d\n", 1, x, y);
		}
	}	
	return 0;
}
