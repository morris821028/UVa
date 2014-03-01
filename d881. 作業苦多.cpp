#include<stdio.h>
main() {
	int d;
	while(scanf("%d", &d) == 1) {
		int sum = 0, a, t = 1;
		for(a = 0; a < 50; a++)
			sum += t, t = 1+(2+a*d)*(a+1)/2;
		printf("%d\n", sum);
	}
	return 0;
}
