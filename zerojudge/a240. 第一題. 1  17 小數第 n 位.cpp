#include<stdio.h>
main() {
	char cycle[20] = "70588235294117647";
	int t, n, sum, i;
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		printf("%c ", cycle[n%16]);
		sum = 72*(n/16);
		for(i = n%16; i >= 1; i--)
			sum += cycle[i]-'0';
		printf("%d\n", sum);
	}
	return 0;
}
