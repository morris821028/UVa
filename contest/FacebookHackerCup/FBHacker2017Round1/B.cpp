#include <bits/stdc++.h>
using namespace std;

int main() {
	int testcase, cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		int N, R;
		scanf("%d %d", &N, &R);
		vector< pair<int, int> > A;
		set<int> SX, SY;
		for (int i = 0; i < N; i++) {
			int x, y;
			scanf("%d %d", &x, &y);
			A.push_back(make_pair(x, y));
			SX.insert(x), SY.insert(y);
		}
		sort(A.begin(), A.end());
		
		int ret = 0;
		for (auto LX : SX) {
			for (auto LY : SY) {
				int cnt = 0;
				vector<int> used(N, 0);
				for (int i = 0; i < N; i++) {
					if (A[i].first >= LX && A[i].first <= LX+R
						&& A[i].second >= LY && A[i].second <= LY+R)
					cnt++, used[i] = 1;
				}
				for (auto TX : SX) {
					for (auto TY: SY) {
						int dd = 0;
						for (int i = 0; i < N; i++) {
							if (used[i])
								continue;
							if (A[i].first >= TX && A[i].first <= TX+R
								&& A[i].second >= TY && A[i].second <= TY+R)
								dd++;
						}
						ret = max(ret, dd+cnt);
					}
				}
			}
		}
		printf("Case #%d: %d\n", ++cases, ret);
	}
	return 0;
}

