#include <stdio.h>
int main() {
	int DP[7500] = {}, M[5] = {1, 5, 10, 25, 50};
	int i, j, n;
	DP[0] = 1;
	for(i = 0; i < 5; i++) {
		for(j = M[i]; j < 7500; j++)
			DP[j] += DP[j-M[i]];
	}
	while(scanf("%d", &n) == 1)
		printf("%d\n", DP[n]);
    return 0;
}
