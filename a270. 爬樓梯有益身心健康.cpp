#include<stdio.h>
int main() {
	int n, A[5], B[8], i, j, x, y, t;
	while(scanf("%d", &n) == 1) {
		int flag = 0;
		for(i = 1; i <= 4; i++)
			scanf("%d", &A[i]);
		for(i = 0; i < 8; i++) {
			scanf("%d", &B[i]);
			if(i) {
				x = B[i], y = B[i-1];
				if(x > y)	t = x, x = y, y = t;
				for(j = x, t = 0; j < y; j++)
					t += A[j];
				if(t > n)	flag = 1;
			}
		}
		puts(flag ? "no" : "yes");
	} 
	return 0;
}
