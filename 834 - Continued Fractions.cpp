#include<stdio.h>
int main() {
	int x, y;
	while(scanf("%d %d", &x, &y) == 2) {
		int A[32], At = 0, tmp, i;
		while(x%y) {
			A[At++] = x/y;
			tmp = x, x = y, y = tmp%y;
		}
		A[At++] = x;
		printf("[%d", A[0]);
		for(i = 1; i < At; i++) {
			if(i == 1)	printf(";");
			else		printf(",");
			printf("%d", A[i]);
		}
		puts("]");
	}
    return 0;
}
