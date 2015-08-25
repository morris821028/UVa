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
		int N = 100000, Q = 100000;
		int cmd;
		int X, Y, K;
		printf("%d\n", N);
		vector<string> A;
		for (int i = 0; i < N; i++) { 
			int m = rand()%5 ? 15 : rand()%10 + 3;
			string aa = "";
			for (int j = 0; j < m; j++) {
				char c = toChar(rand()%62);
				aa += c;
				printf("%c", c);
			}
			A.push_back(aa);
			puts("");
		} 
		printf("%d\n", Q);
		for (int i = 0; i < Q; i++) {
			int m = 128;
			if (rand()%10) {
				for (int j = 0; j < m; j++)
					printf("%c", toChar(rand()%62));
			} else {
				int m = 50;
				for (int j = 0; j < m; j++) {
					if (rand()%10)
						printf("%s", A[rand()*rand()%A.size()].c_str());
					else
						printf("%c", toChar(rand()%62));
				}
			}
			puts("");
		}
	}	
	return 0;
}
