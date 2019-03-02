#include <bits/stdc++.h>
using namespace std;

void normalize(vector<pair<int, int>> &C) {
	int lx = C[0].first, ly = C[0].second;
	for (auto &e : C)
		lx = min(lx, e.first), ly = min(ly, e.second);
	for (auto &e : C)
		e.first -= lx, e.second -= ly;
	sort(C.begin(), C.end());
}
void rotate(vector<pair<int, int>> &C) {
	for (auto &e : C) {
		int x = e.first, y = e.second;
		e.first = y, e.second = -x;
	}
}

int main() {
	int testcase;
	scanf("%d", &testcase);
	while (getchar() != '\n');
	while (testcase--) {
		while (getchar() != '\n');
		set<vector<pair<int, int>>> S;
		int x, y;
		vector<pair<int, int>> C;
		while (scanf("%d,%d", &x, &y) == 2) {
			if (x == -1 && y == -1)
				break;
			C.emplace_back(x, y);
		}
		for (int i = 0; i < 4; i++) {
			normalize(C);
			S.insert(C);
//			for (auto e : C)
//				printf("%d %d, ", e.first, e.second);
//			puts("");
			rotate(C);
		}
		printf("%d\n", S.size());
		if (testcase)
			puts("");
	}
	return 0;
}

/*
1

0,1 0,2 1,1 2,1 2,0 -1,-1
*/
