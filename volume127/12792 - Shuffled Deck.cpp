#include <stdio.h>
#include <algorithm>
using namespace std;

int A[1<<21], used[1<<21] = {};
int testcase = 0;
long long gcd(long long x, long long y) {
	long long t;
	while (x%y)
		t = x, x = y, y = t%y;
	return y;
}
int main() {
	int n;
	while (scanf("%d", &n) == 1) {
		for (int i = 0; i < n; i++) {
			if (i&1)
				A[i] = i/2;
			else
				A[i] = i/2 + n/2;
		}
		
		testcase++;
		long long lcm = 1;
		for (int i = 0; i < n; i++) {
			if (A[i] != i && used[i] != testcase) {
				int ss = 0;
				for (int j = i; used[j] != testcase; j = A[j])
					used[j] = testcase, ss++;
				lcm = lcm / gcd(lcm, ss) * ss;
			}
		}
		printf("%d\n", lcm);
	}
	return 0;
}
/*
4
6
2
100002
*/
