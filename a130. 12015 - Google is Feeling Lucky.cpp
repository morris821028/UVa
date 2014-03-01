#include<stdio.h>
#include<stdlib.h>
main() {
	int T, C = 0, luck[10];
	char www[10][101];
	scanf("%d", &T);
	while(T--) {
		int a, max = 0;
		for(a = 0; a < 10; a++) {
			scanf("%s %d", &www[a], &luck[a]);
			max = (luck[a] > max) ? luck[a] : max;
		}
		printf("Case #%d:\n", ++C);
		for(a = 0; a < 10; a++)
			if(luck[a] == max)
				puts(www[a]);
	}
	return 0;
}
