#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>
#include <assert.h>
using namespace std;

int BIT[256];
int query(int x) {
	int ret = 0;
	for (; x; x -= x&(-x))
		ret += BIT[x];
	return ret;
}
void modify(int x, int L) {
	for (; x <= L; x += x&(-x))
		BIT[x]++;
}
int main() {
	int N, K, r, h, w;
	while (scanf("%d %d", &N, &K) == 2) {
		vector<pair<int, int> > D;
		for (int i = 0; i < N; i++) {
			scanf("%d %d", &r, &h);
			assert(r <= 100 && h <= 100 && r > 0 && h > 0);
			D.push_back(make_pair(r * 2, h));
		}
		int ret = 0x3f3f3f3f;
		sort(D.begin(), D.end());
		memset(BIT, 0, sizeof(BIT));
		for (int i = 0; i < N; i++) {
			modify(D[i].second, 255);
			for (int j = D[i].second; j <= 100; j++) {
				int q = query(j);
				w = D[i].first, h = j;
				if (q >= K)
					ret = min(ret, w*w*h);
			}
		}
		if (K == 0)	ret = 0;
		printf("%d\n", ret);
	}
	return 0;
}
