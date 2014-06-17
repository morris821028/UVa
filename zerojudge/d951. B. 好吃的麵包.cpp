#include<stdio.h>
main() {
	int t, N, X, Y, M;
	scanf("%d", &t);
	while(t--) {
		scanf("%d %d %d %d", &N, &X, &Y, &M);
		int b = (N - M*X) / ( Y - X), a =  M - b;
		printf("%d %d\n", a, b);
	}
	return 0;
}
