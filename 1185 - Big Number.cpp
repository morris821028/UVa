#include<stdio.h>
#include<math.h>
int DP[10000001] = {0};
int main() {
	int t, n, i;
	double last = 0;
	for(i = 1; i <= 10000000; i++) {
		last += log10(i);
		DP[i] = (int)last;
	}
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		printf("%d\n", DP[n]+1);
	}
    return 0;
}
