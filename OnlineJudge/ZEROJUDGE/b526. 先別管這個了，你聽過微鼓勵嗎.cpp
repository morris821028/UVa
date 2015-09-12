#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, m, l, r;
	while (scanf("%d %d", &n, &m) == 2) {
		vector< pair<int, int> > V;
		vector<int> X;
		for (int i = 0; i < m; i++) {
			scanf("%d %d", &l, &r), V.push_back(make_pair(l, r));
			X.push_back(l-1);
			X.push_back(l);
			X.push_back(r);
			X.push_back(r+1);
		}
		sort(X.begin(), X.end());
		sort(V.begin(), V.end());
		X.resize(unique(X.begin(), X.end()) - X.begin());
		multiset<int> S;
		int ret = 0;
		for (int i = 1, pos = 0; i < X.size(); i++) {
			int x = X[i];
			while (!S.empty() && *S.begin() <= X[i-1])
				S.erase(S.begin());
			while (pos < m && V[pos].first == x)
				S.insert(V[pos].second), pos++;
			if (S.size()%2)
				ret += X[i] - X[i-1];
		}
		printf("%d\n", n - ret);
	}
	return 0;
}