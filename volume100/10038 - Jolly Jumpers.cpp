#include<stdio.h>
#include<stdlib.h>
int main() {
	int n, A[3001], i;
	while(scanf("%d", &n) == 1) {
		for(i = 0; i < n; i++)
			scanf("%d", &A[i]);
		int mark[3001] = {0}, flag = 0;
		for(i = 1; i < n; i++) {
			if(abs(A[i] - A[i-1]) < n)
				mark[abs(A[i] - A[i-1])]++;
		}
		for(i = 1; i < n; i++)
			if(mark[i] == 0)
				flag = 1;
		if(flag)
			puts("Not jolly");
		else
			puts("Jolly");
	}
    return 0;
}
