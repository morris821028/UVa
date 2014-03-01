#include<stdio.h>
main() {
	int n, x, t = 0, A = 0, stack[100000] = {};
	scanf("%d", &n);
	while(n--) {
		scanf("%d %d", &x, &x);
		while(x < stack[t]) A++, t--;
		if(x != stack[t]) stack[++t] = x;
	}
	printf("%d\n", A + t);
	return 0;
}
