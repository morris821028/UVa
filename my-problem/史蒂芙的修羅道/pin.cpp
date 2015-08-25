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

const int MAXN = 65536;

int main() {
//	sieve();
	srand (time(NULL));
	int testcase, n, m, x, y, a, b;
	freopen("in.txt", "w+t", stdout);
	testcase = 1; 
	while (testcase--) {
		int N = 5000000, Q = 5000000;
		int cmd;
		int X, Y, K;
//		printf("%d %d %d\n", N, Q, 10);
		printf("%d %d %d\n", N, Q, rand() * rand());
//		for (int i = 1; i <= N; i++) { 
//			printf("%d%c", rand() * rand(), i == N ? '\n' : ' ');
//		} 
//		printf("%d\n", Q);
//		for (int i = 1; i <= Q; i++)
//			printf("%d %d\n", rand()*rand()%N+1, rand()*rand()%N+1);
	}	
	return 0;
}
