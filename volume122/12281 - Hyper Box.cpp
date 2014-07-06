#include <stdio.h> 
#include <algorithm>
using namespace std;

int main() {
	long long f[50] = {1, 2};
	for(int i = 2; i < 50; i++)
		f[i] = f[i-1] + f[i-2];
	int testcase, cases = 0, N, x;
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d", &N);
		long long ret = 1;
		for(int i = 0; i < N; i++) {
			scanf("%d", &x);
			int cnt = 0;
			for(int j = 49; j >= 0; j--)
				if(x >= f[j])
					x -= f[j], cnt++;
			ret *= cnt;
		}
		printf("Case %d: %lld\n", ++cases, ret);
	}
	return 0;
}
