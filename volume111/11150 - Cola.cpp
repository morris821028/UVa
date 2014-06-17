#include <stdio.h>
int main() {
	int n;
	while(scanf("%d", &n) == 1) {
		int sum = n;
		while(n >= 3) {
			sum += n/3;
			n = n/3 + n%3;
		}
		if(n == 2)	sum++;
		printf("%d\n", sum);
	}
    return 0;
}
