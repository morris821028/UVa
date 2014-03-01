#include<stdio.h>
main() {
	int DP[14][14] = {}, a, b, t;
	DP[1][1] = 1;
	for(a = 2; a <= 13; a++)
		for(b = 1; b <= a; b++)
			DP[a][b] = DP[a-1][b] + DP[a-1][b-1];
	scanf("%d", &t);
	while(t--) {
		scanf("%d %d", &a, &b);
		printf("%d\n", DP[a][b]);
	}
	return 0;
}
