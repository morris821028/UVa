#include <bits/stdc++.h> 
using namespace std;
// greedy
int main() {
	int n, m, cases = 0;
	const int MAXD = 300;
	while (scanf("%d", &n) == 1 && n) {
		vector<int> A[MAXD+5];
		for (int i = 0; i < n; i++) {
			int p, d;
			scanf("%d %d", &p, &d);
			A[d].push_back(p);
		}
		
		vector<int> D[MAXD+5];
		
		scanf("%d", &m);
		for (int i = 0; i < m; i++) {
			int p, hh, mm;
			scanf("%d %d:%d", &p, &hh, &mm);
			hh = min(hh*60 + mm - 14*60, MAXD);
			D[hh].push_back(p);
		}
		
		multiset<int> S;
		for (int i = 0; i <= MAXD; i++) {
			for (auto e: A[i])	S.insert(e);
			
			sort(D[i].begin(), D[i].end());
			for (auto e: D[i]) {
				auto it = S.upper_bound(e);
				if (it != S.begin())
					it--;
				if (it != S.end() && *it <= e)
					S.erase(it);
			}
		}
		
		int tent = 0, tent_p = 0;
		for (auto e : S)
			tent++, tent_p += e;
		printf("Trial %d: %d %d\n\n", ++cases, tent, tent_p);
	}
	return 0;
}
/*
1
20 60
1
30 16:00
2
20 60
50 30
1
30 14:50

2
29 0
30 0
1
30 14:00
*/
