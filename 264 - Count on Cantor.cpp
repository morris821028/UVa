#include<stdio.h>
int main() {
	int n;
	while(scanf("%d", &n) == 1) {
		int i, line, sum = 0;
		for(i = 1; ; i++) { 
			sum += i;
			if(sum >= n) {
				line = i;
				break;
			}
		} 
		printf("TERM %d IS ", n);
		if(line&1)
			printf("%d/%d\n", 1+sum-n, line-(sum-n));
		else
			printf("%d/%d\n", line-(sum-n), 1+sum-n);
	}
    return 0;
}
