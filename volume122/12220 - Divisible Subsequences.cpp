#include <stdio.h>
#include <map>
using namespace std;

int main() {
	int testcase, d, n, x;
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d %d", &d, &n);
		map<int, int> hash[1024];
		hash[0][0] = 1;
		long long ret = 0, sum = 0;
		for(int i = 0; i < n; i++) {
			scanf("%d", &x);
			sum += x;
			sum %= d;
			ret += hash[sum&1023][sum];
			hash[sum&1023][sum]++;
		}
		printf("%lld\n", ret);
	}
	return 0;
}
/*
2  
7 3
1 2 3
4 8
2 1 2 1 1 2 1 2
*/
