#include <bits/stdc++.h>
using namespace std;

void trans(int N, int B, int f = 0) {
	if (f == 1 && N == 0)
		printf("0");
	if (N == 0)
		return ;
	int p = N % B;
	if (p < 0)	p -= B;
	trans((N - p) / B, B);
	putchar(p < 10 ? p + '0' : p - 10 + 'A');
}
int main() {
	int N, B;
	while (scanf("%d %d", &N, &B) == 2) {
		printf("%d=", N);
		trans(N, B, 1);
		printf("(base%d)\n", B);
	}
	return 0;
}
