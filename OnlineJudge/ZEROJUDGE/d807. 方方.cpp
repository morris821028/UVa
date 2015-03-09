#include<stdio.h>
int gcd(int x, int y) {
	int t;
	while(x%y) {
		t = x, x = y, y = t%y; 
	}
	return y; 
}
main() {
	int n, m;
	while(scanf("%d %d", &n, &m) == 2) {
		printf("%d\n", gcd(n, m));
	}
	return 0;
}
