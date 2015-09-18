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

char toChar(int x) {
	if (x < 10)	
		return x + '0';
	if (x < 10 + 26)	
		return x - 10 + 'A';
	if (x < 10 + 26 + 26)
		return x - 26 - 10 + 'a';
	assert(false);
	return -1;
}
int main() {
//	sieve();
	srand (time(NULL));
	int testcase, n, m, x, y, a, b;
	freopen("in.txt", "w+t", stdout);
	testcase = 1; 
	while (testcase--) {
		int N = 1000, M = 1000, Q = 100000;
		int cmd;
		int X, Y, K;
		printf("%d %d\n", N, M);
		printf("%d\n", Q);
		for (int i = 0; i < Q; i++) { 
			int x, y, n, m;
			int lx, ly, rx, ry;
			x = rand()%N+1;
			y = rand()%M+1;
			n = rand()%N+1;
			m = rand()%M+1;
			lx = max(1, x-n);
			ly = max(1, y-m);
			rx = min(N, x+n);
			ry = min(M, y+m);
//			lx = rand()%(N)+1;
//			rx = rand()%(N)+1;
//			ly = rand()%(M)+1;
//			ry = rand()%(M)+1;
			if (lx > rx)	swap(lx, rx);
			if (ly > ry)	swap(ly, ry);
			printf("%d %d %d %d\n", lx, ly, rx, ry);
		} 
//		puts("");
	}	
	return 0;
}
