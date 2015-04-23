#include <stdio.h> 
// greedy
int swapCnt(int n) { // split circle into 2 array, inverse 2 array
	int a = n/2, b = n - n/2;
	return a * (a-1)/2 + b * (b-1)/2;
}
int main() {
	int testcase, n;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		printf("%d\n", swapCnt(n));
	}
	return 0;
}

