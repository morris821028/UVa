#include <bits/stdc++.h>
using namespace std;

int main() {
	int testcase, cases;
	scanf("%d", &testcase);
	while (testcase--) {
		int N, J;
		scanf("%d %d", &N, &J);
		printf("Case #%d:\n", ++cases);
		set<long long> R;
		for (int i = 2; i < N && J; i++) {
			if (N%i)	continue;
			for (int j = 0; j < (1<<(i-2)) && J; j++) {
				int mask = (j<<1)|1|(1<<(i-1));
				long long v = 0;
				for (int k = 0; k < N/i; k++)
					v = (v<<i) | mask;
				if (R.count(v))	continue;
				R.insert(v);
				for (int k = N-1; k >= 0; k--)
					printf("%d", (v>>k)&1);
				for (int B = 2; B <= 10; B++) {
					long long div = 0, nn = 0;
					for (int k = i-1; k >= 0; k--)
						div = div * B + ((mask>>k)&1);
					for (int k = N-1; k >= 0; k--)
						nn = nn * B + ((v>>k)&1);
//					assert(nn % div == 0 && nn != div);
					printf(" %lld", div);
				}
				puts("");
				J--;
			}
		}
		assert(J == 0);
	}
	return 0;
}
/*
1
16 3
*/
