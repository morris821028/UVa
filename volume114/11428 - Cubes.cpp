#include <stdio.h>

int main() {
	int i, j;
	int x[10001], y[10001];
	int hasAns[10001] = {};
	for(i = 2; i <= 60; i++) {
		for(j = i-1; j >= 1; j--) {
			if(i*i*i - j*j*j <= 10000 && hasAns[i*i*i - j*j*j] == 0) {
				hasAns[i*i*i - j*j*j] = 1;
				x[i*i*i - j*j*j] = i;
				y[i*i*i - j*j*j] = j;
			}
		}
	}
	int n;
	while(scanf("%d", &n) == 1 && n) {
		if(hasAns[n])
			printf("%d %d\n", x[n], y[n]);
		else
			puts("No solution");
	}
    return 0;
}
