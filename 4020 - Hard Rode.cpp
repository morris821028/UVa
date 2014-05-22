#include <stdio.h> 
#include <algorithm>
#include <math.h>
using namespace std;

int main() {
	int L, N, T, cases = 0;
	long long speed[10];
	while(scanf("%d %d %d", &L, &N, &T) == 3 && L) {
		int p[10] = {};
		for(int i = 0; i < N; i++) {
			scanf("%lld", &speed[i]);
			p[i] = i;
		}
		sort(speed, speed + N);
		long long ret = 0x3f3f3f3f;
		do {
			double start = T, lastTime = L / speed[p[0]];
			for(int i = 1; i < N; i++) {
				double time = L / speed[p[i]] + start;
				if(time >= lastTime) {
					start += T;
					lastTime = time;
				} else {
					lastTime = 0x3f3f3f3f;
					break;
					// start += T + (lastTime - time);
				}
			}
			ret = min(ret, (long long) ceil(lastTime));
		} while (next_permutation(p, p + N));
		printf("Case %d: %lld\n", ++cases, ret);
	}
	return 0;
}
