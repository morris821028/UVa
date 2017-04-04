#include <bits/stdc++.h>
using namespace std;

int main() {
	int N, Q, X[3000], Y[3000];
	while (scanf("%d %d", &N, &Q) == 2 && N) {
		for (int i = 0; i < N; i++)
			scanf("%d %d", &X[i], &Y[i]);
			
		int C[65536] = {};
		for (int i = 0; i < N; i++) {
			for (int j = i+1; j < N; j++) {
				int dx = X[i] - X[j];
				int dy = Y[i] - Y[j];
				int dist = dx*dx + dy*dy;
				int sq = ceil(sqrt(dist));
				C[sq]++;
			}
		}
		
		for (int i = 1; i < 65536; i++)
			C[i] += C[i-1];
		for (int i = 0; i < Q; i++) {
			int R;
			scanf("%d", &R);
			printf("%.2lf\n", C[R]*2.f/N+1);
		}
		puts("");
	}
	return 0;
}
