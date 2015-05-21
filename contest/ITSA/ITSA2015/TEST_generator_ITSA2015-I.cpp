#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <set>
#include <iostream>
#include <algorithm>
using namespace std;
#define eps 1e-6
double random() {
	int r = rand();
	return (double) r / RAND_MAX;
}
int toChar(int x) {
	if (x < 10)
		return x + '0';
	return x - 10 + 'A';
}
main() {
	int n, m, t, a, b, c, tmp;
	int z, i, j, k, l, p, q;
	srand ( time(NULL));
	freopen("in.txt", "w+t", stdout);

	int T = 5;
	printf("%d\n", T);
	while(T--) {
		int n = 50000, p = rand()%4+1;
		printf("%d %d\n", n, p);
		set<string> S;
		for (int i = 0; i < n; i++) {
			char s[8] = {};
			do {
				for (int j = 0; j < 4; j++)
					s[j] = toChar(rand()%36);
			} while (S.count(s));
			S.insert(s);
			puts(s);
		}
		puts("");
	}
	
	return 0;
}
