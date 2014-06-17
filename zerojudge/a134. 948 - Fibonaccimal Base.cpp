#include<stdio.h>
main() {
	int F[39] = {};
	int a, n, t;
	F[0] = 1, F[1] = 2;
	for(a = 2; a < 39; a++)
		F[a] = F[a-1] + F[a-2];
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		printf("%d = ", n);
		int flag = 0;
		for(a = 38; a >=0; a--) {
			if(n / F[a] == 1) {
				printf("1");
				n %= F[a], flag = 1;
			}
			else if(flag)
				printf("0");
		}
		printf(" (fib)\n");
	}
	return 0;
}
