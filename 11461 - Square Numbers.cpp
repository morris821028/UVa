#include <stdio.h>
int main() {
	int DP[100001] = {};
	int a, b;
	for(a = 1; a*a <= 100000; a++)
		DP[a*a] = 1;
	for(a = 1; a <= 100000; a++)
		DP[a] += DP[a-1];
	while(scanf("%d %d", &a, &b) == 2) {
		if(a == 0 && b == 0)
			break;
		printf("%d\n", DP[b]-DP[a-1]);
	}
    return 0;
}
