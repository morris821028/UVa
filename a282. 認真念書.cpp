#include<stdio.h>
#include<string.h>
int main() {
	int n, x;
	char mark[2001];
	while(scanf("%d", &n) == 1) {
		memset(mark, 0, sizeof(mark));
		while(n--)
			scanf("%d", &x), mark[x] = 1;
		x = 1;
		while(mark[x] == 1)
			x++;
		printf("%d\n", x);
	}
	return 0;
}
