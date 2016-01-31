#include <bits/stdc++.h>
using namespace std;

int main() {
	int cases = 0;
	int N, M;
	while (scanf("%d %d", &N, &M) == 2) {
		if (cases++)	puts("");
		
		int cnt[128] = {}, mx = 0;
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= M; j++)
				cnt[i+j]++;
		}
		for (int i = 1; i <= N+M; i++)
			mx = max(mx, cnt[i]);
		for (int i = 1; i <= N+M; i++) {
			if (cnt[i] == mx)
				printf("%d\n", i);
		}
	}
	return 0;
}

