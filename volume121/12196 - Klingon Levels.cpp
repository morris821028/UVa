#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	int N, M, x;
	while(scanf("%d", &N) == 1 && N) {
		vector<int> D[100005];
		for(int i = 0; i < N; i++) {
			scanf("%d", &M);
			for(int j = 0; j < M; j++)
				scanf("%d", &x), D[i].push_back(x);
			sort(D[i].begin(), D[i].end());
		}
		int ret = 0x3f3f3f3f;
		int idx[100005];
		for(int i = 0; i < N; i++)
			idx[i] = -1;
		for(int i = 0; i <= 1000; i++) {
			int sum = 0;
			for(int j = 0; j < N; j++) {
				while(idx[j]+1 < D[j].size() && D[j][idx[j]+1] < i)
					idx[j]++;
				sum += abs((int)D[j].size() - 2 * (idx[j] + 1));
			}
			ret = min(ret, sum);
		}
		printf("%d\n", ret);
	}
	return 0;
}
