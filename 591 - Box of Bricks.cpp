#include <stdio.h>
#include <stdlib.h>
int main() {
	int n, H[50], i, Case = 0;
	while(scanf("%d", &n) == 1 && n) {
		int sum = 0, Ans = 0;
		for(i = 0; i < n; i++)
			scanf("%d", &H[i]), sum += H[i];
		sum /= n;
		for(i = 0; i < n; i++) {
			Ans += abs(H[i] - sum);
		}
		Ans /= 2;
		printf("Set #%d\n", ++Case);
		printf("The minimum number of moves is %d.\n\n", Ans);
	}
    return 0;
}
