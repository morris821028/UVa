#include <stdio.h> 
#include <algorithm>
using namespace std;

int main() {
	int N;
	long long X[1024], Y[1024];
	while(scanf("%d", &N) == 1 && N) {
		for(int i = 0; i < N; i++)
			scanf("%lld %lld", &X[i], &Y[i]); 
		long long d[1024];
		long long ret = 0;
		for(int i = 0; i < N; i++) {
			for(int j = 0; j < N; j++)
				d[j] = (X[i] - X[j]) * (X[i] - X[j]) +
						(Y[i] - Y[j]) * (Y[i] - Y[j]);
			sort(d, d+N);
			long long cnt = 1;
			d[N] = -1;
			for(int j = 1; j <= N; j++) {
				if(d[j] != d[j-1]) {
					ret += cnt * (cnt-1) /2;
					cnt = 1;
				} else {
					cnt++;
				}
			} 
		}
		printf("%lld\n", ret);
	}
	return 0;
}
