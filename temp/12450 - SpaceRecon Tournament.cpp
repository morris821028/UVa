#include <stdio.h>
#include <iostream>
#include <algorithm>
using namespace std;

bool wcmp(pair<string, int> a, pair<string, int> b) {
	return a.second > b.second;
}
bool lcmp(pair<string, int> a, pair<string, int> b) {
	return a.first < b.first;
}
int main() {
	int testcase, n, w;
	char s[1024];
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		n = 1<<n;
		pair<string, int> D[1024];
		for (int i = 0; i < n; i++) {
			scanf("%s %d", s, &w);
			D[i] = make_pair(s, w);
		}
		sort(D, D + n, wcmp);
		int round = 1;
		for (int i = 1; i < n; i += round, round *= 2)
			sort(D + i, D + i + round, lcmp);
		for (int i = 0; i < n; i++)
			printf("%s\n", D[i].first.c_str());
	}
	return 0;
}
