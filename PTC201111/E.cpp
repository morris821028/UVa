#include<stdio.h>
#include<stdlib.h>
#include<math.h>
int main() {
	int n;
	long long Ans[50000][2], At, i;
	while(scanf("%d", &n) == 1 && n) {
		At = 0;
		long long sqrn = (long long)sqrt(n);
		for(i = 1; i <= sqrn; i++) {
			long long another = n - i*i;
			another = (long long)sqrt(another);
			if(i*i + another*another == n && i <= another) {
				Ans[At][0] = i;
				Ans[At][1] = another;
				At++;
			}
		}
		if(At && sqrn*sqrn == n) {
			printf("%lld ", At);
			for(i = 0; i < At-1; i++)
				printf("(%lld %lld) ", Ans[i][0]*Ans[i][0], Ans[i][1]*Ans[i][1]);
			printf("(%lld %lld)\n", Ans[i][0]*Ans[i][0], Ans[i][1]*Ans[i][1]);
		} else
			printf("0\n");
	}
	return 0;
}
