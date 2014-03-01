#include<stdio.h>
int main() {
	int n;
	while(scanf("%d", &n) == 1 && n >= 0) {
		int x = 5+n*5, i, j = x, tn = n;
		for(i = 1; x > 0; i++) {
			x--;
			if(tn > 0) {
				x -= tn;
				tn = n - (j-x)/5;
			}
		}
		printf("%d\n", i-1);
	}
	return 0;
}
