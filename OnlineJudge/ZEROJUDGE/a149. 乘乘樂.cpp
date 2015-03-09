#include<stdio.h>
main() {
	int a, n, x;
	char s[11];
	scanf("%d ", &n);
	while(n--) {
		for(gets(s), a = 0, x = 1; s[a]; a++)
			x *= s[a]-'0';
		printf("%d\n", x);
	}
	return 0;
}
