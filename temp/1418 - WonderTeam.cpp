// greedy
#include <stdio.h> 
/*
| team | #win | #lost | #draw | score |
| ---- |------|-------|-------|-------| 
|wonder|   2  |   n-1 | n - 3 | n + 3 |
|2 lost|   1  |   1   | 2n - 4| 2n - 1|
| other|   1  |   0   | 2n - 3| 2n    |
*/
int main() {
	int n;
	while (scanf("%d", &n) == 1 && n) {
		if (n <= 3)
			puts("1");
		else if (n == 4)
			puts("2");
		else
			printf("%d\n", n);
	}
	return 0;
}
