#include <stdio.h>

int main() {
	int N, X[100005];
	const int mod = 10001;
	while(scanf("%d", &N) == 1) {
		for(int i = 0; i < N; i++)
			scanf("%d", &X[i]);
		int ra, rb;
		for(int a = 0; a < mod; a++) {
			for(int b = 0; b < mod; b++) {
				int x = X[0], f = 1;
				for(int i = 0; i < N; i++) {
					if(x != X[i]) {
						f = 0;break;
					}
					x = (a * x + b)%mod;
					x = (a * x + b)%mod;
				}
				if(f) {
					ra = a, rb = b;
					a = mod, b = mod;
				}
			}
		}
		for(int i = 0; i < N; i++)
			printf("%d\n", (ra * X[i] + rb) % mod);
	}
	return 0;
}
