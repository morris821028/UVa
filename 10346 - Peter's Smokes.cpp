#include <stdio.h>
int main() {
	int n, k;
	while(scanf("%d %d", &n, &k) == 2) {
		int sum = n, used = n;
		while(used >= k) {
			n = used/k;
			used = used%k + n;
			sum += n;
		}
		printf("%d\n", sum);
	}
    return 0;
}
