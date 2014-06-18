#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	int testcase, L, R;
	scanf("%d", &testcase);
	while(testcase--) {
		vector< pair<int, int> > M;
		while(scanf("%d %d", &L, &R) == 2 && L + R) {
			M.push_back(make_pair(R, L));
		}
		sort(M.begin(), M.end());
		int ret = 0;
		L = 0;
		for(int i = 0; i < M.size(); i++) {
			if(L <= M[i].second) {
				L = M[i].first;
				ret++;
			}
		}
		printf("%d\n", ret);
	}
	return 0;
}
/*
3
0 6
5 7
8 9
5 9
1 2
3 4
0 5
0 0
6 10
5 6
0 3
0 5
3 5
4 5
0 0
1 5
3 9
0 0
*/
