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
	return x + 'a';
}
main() {
	int n, m, t, a, b, c, tmp;
	int z, i, j, k, l, p, q;
	srand ( time(NULL));
	freopen("in.txt", "w+t", stdout);

	int T = 100000;
	n = 10000;
	vector<string> 	name;
	vector<int>		dc;
	for (int i = 0; i < n; i++) {
		int l = rand()%10+1;
		string s = "";
		for (int j = 0; j < l; j++)
			s += toChar(rand()%10);
		name.push_back(s);
		dc.push_back(0);
	}
	while(T--) {
		if (rand()%100 > 0) {
			int idx = rand()%n;
			dc[idx] = max(min(dc[idx] + rand()%20 - 5, 32767), 0);
			printf("1 %s %d\n", name[idx].c_str(), dc[idx]);
		} else {
			printf("2 %d\n", rand()%5+5);
		}
	}
	
	return 0;
}
