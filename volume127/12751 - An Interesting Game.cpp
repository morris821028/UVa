#include <stdio.h> 
int f(int n) {
	return (n)*(n+1)/2;
}
int main() {
	scanf("%*d");
	int N, K, X;
	int cases = 0;
	while(scanf("%d %d %d", &N, &K, &X) == 3)
		printf("Case %d: %d\n", ++cases, f(N)-f(X+K-1)+f(X-1));
	return 0;
} 
