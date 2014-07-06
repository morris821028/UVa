#include <stdio.h> 
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	int testcase, N, K, l, r;
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d %d", &K, &N);
		vector< pair<int, int> > D;
		for(int i = 0; i < N; i++) {
			scanf("%d %d", &l, &r);
			if(l > r)	swap(l, r);
			D.push_back(make_pair(r, l));
		}
		sort(D.begin(), D.end());
		
		int used[20005] = {}, ret = 0;
		const int shift = 10000;
		for(int i = 0; i < N; i++) {
			int has = 0, l = D[i].second, r = D[i].first;
			for(int j = l; j <= r; j++)
				has += used[j + shift];
			for(int j = r; j >= l && has< K; j--)
				if(!used[j + shift])
					has++, used[j + shift] = 1, ret++;
		}
		printf("%d\n", ret);
		for(int i = 0; i < 20005; i++)
			if(used[i])
				printf("%d\n", i - shift);
		if(testcase)
			puts("");
	}
	return 0;
}
