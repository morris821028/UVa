#include <bits/stdc++.h>
using namespace std;

int main() {
	int a, c, m, x, q, n;
	while (scanf("%d %d %d %d", &a, &c, &m, &x) == 4) {
		scanf("%d %d", &q, &n);
		x %= m;
		int cnt[1024] = {}, path[1024] = {}, f[1024];
		for (int i = 1; i <= n; i++) {
			f[i] = x;
			if (path[x]) {
				for (int j = path[x]-1; j >= 1; j--)
					cnt[f[j]]++;
				int clen = i - path[x];
				assert(clen != 0);
				for (int j = path[x]; j < i; j++)
					cnt[f[j]] += (n - path[x]) / clen + (j - path[x] <= (n - path[x]) % clen);
				break;
			}
			path[x] = i;
			if (i == n) {
				for (int i = 1; i <= n; i++)
					cnt[f[i]]++;
				break;
			}
			x = (a * x + c)%m;
		}
		int sum = 0;
		vector< pair<int, int> > T;
		for (int i = 0; i < m; i++) {
			if (cnt[i]) {
				sum += cnt[i];
				T.push_back(make_pair(sum, i));
			}
		}
		for (int i = 0; i < q; i++) {
			int t;
			scanf("%d", &t);
			int pos = int(lower_bound(T.begin(), T.end(), make_pair(t, -1)) - T.begin());
			printf("%d\n", T[pos].second);
		}
	}
	return 0;
}
