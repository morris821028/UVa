#include <stdio.h>
#include <map>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
	int n, m;
	char s1[32], s2[32];
	while (scanf("%d", &n) == 1) {
		map<int, int> A[1024];
		string X[1024], Y[1024];
		map<string, int> R, P;
		for (int i = 0; i < n; i++) {
			scanf("%s %d %s", s1, &m, s2);
			int &x = R[s2], &y = P[s1];
			if (x == 0)	x = R.size(), X[x] = s2;
			if (y == 0)	y = P.size(), Y[y] = s1;
			A[x][y] += m;
		}
		for (int i = 1; i <= R.size(); i++) {
			printf("%s ", X[i].c_str());
			for (map<int, int>::iterator it = A[i].begin();
				it != A[i].end(); it++)
				printf("%c %s %d", it == A[i].begin() ? ':' : ',', Y[it->first].c_str(), it->second);
			puts("");
		}
	}
	return 0;
}
