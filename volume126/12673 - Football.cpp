#include <stdio.h>
#include <algorithm>
#include <vector>
using namespace std;

bool cmp(pair<int, int> x, pair<int, int> y) {
	return x.first - x.second > y.first - y.second;
}
int main() {
	int N, G, S, R;
	while(scanf("%d %d", &N, &G) == 2) {
		vector< pair<int, int> > D;
		for(int i = 0; i < N; i++) {
			scanf("%d %d", &S, &R);
			D.push_back(make_pair(S, R));
		}
		sort(D.begin(), D.end(), cmp);
		int ret = 0;
		for(int i = 0; i < N; i++) {
			S = D[i].first, R = D[i].second;
			if(S > R)
				ret += 3;
			else if(S == R) {
				if(G)
					ret += 3, G--;
				else
					ret += 1;
			} else {
				if(G > R - S)
					ret += 3, G -= R - S + 1;
				else if(G == R - S)
					ret += 1, G = 0;	
			}
		}
		printf("%d\n", ret);
	}
	return 0;
}
/*
2 1
1 1
1 1
3 2
1 3
3 1
2 2
4 10
1 1
2 2
1 3
0 4
*/
