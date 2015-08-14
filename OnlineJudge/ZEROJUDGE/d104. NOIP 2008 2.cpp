#include <bits/stdc++.h>
using namespace std;

bool cmp(pair<int, int> a, pair<int, int> b) {
	if (a.first != b.first)
		return a.first > b.first;
	return a.second < b.second;
}
int main() {
	int N, M, K, L, D;
	while (scanf("%d %d %d %d %d", &N, &M, &K, &L, &D) == 5) {
		int A[1024] = {}, B[1024] = {};
		for (int i = 0; i < D; i++) {
			int x1, x2, y1, y2;
			scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
			if (x1 == x2)
				B[min(y1, y2)]++;
			else
				A[min(x1, x2)]++;
		}
		vector< pair<int, int> > C, D;
		for (int i = 1; i <= M; i++)
			C.push_back({A[i], i});
		for (int i = 1; i <= N; i++)
			D.push_back({B[i], i});
		sort(C.begin(), C.end(), cmp);
		sort(D.begin(), D.end(), cmp);
		C.resize(K), D.resize(L);
		
		vector<int> OX, OY;
		for (int i = 0; i < C.size(); i++)
			OX.push_back(C[i].second);
		for (int i = 0; i < D.size(); i++)
			OY.push_back(D[i].second);
		sort(OX.begin(), OX.end());
		sort(OY.begin(), OY.end());
		OX.resize(unique(OX.begin(), OX.end())- OX.begin());
		OY.resize(unique(OY.begin(), OY.end())- OY.begin());
		for (int i = 0; i < OX.size(); i++)
			printf("%d%c", OX[i], i == OX.size()-1 ? '\n' : ' ');
		for (int i = 0; i < OY.size(); i++)
			printf("%d%c", OY[i], i == OY.size()-1 ? '\n' : ' ');
	}
	return 0;
}
