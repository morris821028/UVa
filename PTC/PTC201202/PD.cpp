#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
int main() {
	int N, B, j;
	while(scanf("%d %d", &N, &B) == 2) {
		double DP[4001], p[100];
		int i, c[100];
		for(i = 0; i <= B; i++)		DP[i] = 1.00;
		for(i = 0; i < N; i++) {
			scanf("%d %lf", &c[i], &p[i]);
		}
		for(i = 0; i < N; i++) {
			for(j = B; j >= c[i]; j--)
				if(DP[j] > DP[j-c[i]]*p[i])
					DP[j] = DP[j-c[i]]*p[i];
		}
		double min = 1.00;
		for(i = 0; i <= B; i++)
			min = min < DP[i] ? min : DP[i];
		printf("%lf\n", log10(min));
	}
    return 0;
}
