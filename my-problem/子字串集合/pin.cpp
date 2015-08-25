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
		int N = 10, Q = 100000;
		int cmd;
		int X, Y, K;
		for (int i = 0; i < N; i++) { 
			char c = rand()%26 + 'A';
			printf("%c", c);
		} 
		puts("");
	}	
	return 0;
}
