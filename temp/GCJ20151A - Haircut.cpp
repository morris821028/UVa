#include <stdio.h>

int main() {
	int testcase, cases = 0;
	int N, B;
	long long M[1024];
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &B, &N);
		for (int i = 0; i < B; i++)
			scanf("%lld", &M[i]);
		
		long long l = 0, r = 100000LL * N, mid, time = 0;
		while (l <= r) {
			mid = (l + r)/2;
			long long cnt = 0;
			for (int i = 0; i < B; i++)
				cnt += mid / M[i] + 1;
			if (cnt >= N)
				r = mid - 1, time = mid;
			else
				l = mid + 1;
		}
		
		long long cnt = 0;
		int id = 0;
		
		for (int i = 0; i < B; i++)
			cnt += time / M[i] +(time % M[i] !=0);
		
		cnt = N - cnt;
//		printf("%lld %lld\n", cnt, time);
		for (int i = 0; i < B; i++) {
			if (time % M[i] == 0) {
				cnt--;
				if (cnt == 0)
					id = i;
			}
		}
		printf("Case #%d: %d\n", ++cases, id + 1);
	}
	return 0;
}
