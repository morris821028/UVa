#include <stdio.h>
#include <algorithm>
using namespace std;
int N, M, L[100005], R[100005], qx, qy;
int main() {
	while(scanf("%d %d", &N, &M) == 2 && N+M) {
		for(int i = 0; i < N; i++) {
			scanf("%*d %*d %d %d", &L[i], &R[i]);
			R[i] += L[i];
		}
		for(int i = 0; i < M; i++) {
			scanf("%d %d", &qx, &qy);
			qy += qx;
			int ret = 0;
			for(int j = 0; j < N; j++) {
				ret += max(qx, L[j]) < min(qy, R[j]);
			}
			printf("%d\n", ret);
		}
	}
	return 0;
}
