#include <bits/stdc++.h>
using namespace std;

const int MAXN = 512;
int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		int n;
		pair<int, int> A[MAXN];
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			int s, d;
			scanf("%d %d", &s, &d);
			A[i] = make_pair(s, d);
		}
		
		// sort with deadline
		sort(A, A+n, [](const pair<int, int> &a, const pair<int, int> &b) -> bool {
			if (a.second != b.second)
				return a.second < b.second;
			return a.first < b.first; 
		});
		
		// get the optimal solution about the minimum of maximum penalty
		pair<int, int> pcost[2] = {{0, -1}, {0, -1}};
		for (int i = 0, w = 0; i < n; i++) {
			w += A[i].first;
			int penalty = max(0, w-A[i].second);
			if (penalty >= pcost[1].first) {
				pcost[1] = {penalty, i};
				if (pcost[1].first >= pcost[0].first)
					swap(pcost[0], pcost[1]);
			}
		}
		
		// try the find the minimum sum of first two maximum penalty,
		// we need to make the maximum penalty smaller
		int ret = pcost[0].first + pcost[1].first;
		int mx_pos = max(pcost[0].second, pcost[1].second);
		for (int i = 0; i < mx_pos; i++) {
			// move i-th task to behind the last maximum penalty.
			pair<int, int> pcost[2] = {{0, -1}, {0, -1}};
			int w = 0;
			for (int j = 0; j <= mx_pos; j++) {
				if (i == j)
					continue;
				w += A[j].first;
				int penalty = max(0, w-A[j].second);
				if (penalty >= pcost[1].first) {
					pcost[1] = {penalty, j};
					if (pcost[1].first >= pcost[0].first)
						swap(pcost[0], pcost[1]);
				}
			}
			w += A[i].first;
			int penalty = max(0, w-A[i].second);
			if (penalty >= pcost[1].first) {
				pcost[1] = {penalty, i};
				if (pcost[1].first >= pcost[0].first)
					swap(pcost[0], pcost[1]);
			}
			ret = min(ret, pcost[0].first+pcost[1].first);
		}
		printf("%d\n", ret);
	}
	return 0;
}
/*
3
6
1  7
4  7
2  4
2  15
3  5
3  8

7
2  17
2  11
3  4
3  20
1  20
4  7
5  14

10
2  5
2  9
5  10
3  11
3  4
4  21
1  7
2  9
2  11
2  23
*/
