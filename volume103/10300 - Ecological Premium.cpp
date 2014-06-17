#include<stdio.h>
int main() {
	int n, f;
	scanf("%d", &n);
	while(n--) {
		scanf("%d", &f);
		long long sum = 0;
		int i, x, y, z;
		for(i = 0; i < f; i++) {
			scanf("%d %d %d", &x, &y, &z);
			sum += x*z;
		}
		printf("%lld\n", sum);
	}
    return 0;
}
