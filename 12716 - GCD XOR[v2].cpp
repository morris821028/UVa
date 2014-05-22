#include <stdio.h>
using namespace std;

int F[30000005] = {};
int main() {
	for(int i = 1; i <= 30000000; i++) {
		for(int j = i << 1; i + j <= 30000000; j += i) {
			if(((i + j)&(j)) == j)
				F[i + j]++;
		}
	}
	for(int i = 1; i <= 30000000; i++)
		F[i] += F[i-1];
	int testcase, cases = 0, n;
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d", &n);
		printf("Case %d: %d\n", ++cases, F[n]);
	}
	return 0;
}
