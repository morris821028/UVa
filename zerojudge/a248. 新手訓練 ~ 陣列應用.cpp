#include<stdio.h>
int main() {
	int a, b, N;
	while(scanf("%d %d %d", &a, &b, &N) == 3) {
		printf("%d.", a/b), a %= b;
		while(N--)
			a *= 10, printf("%c", a/b+'0'),	a %= b;
		puts("");
	} 
	return 0;
}
