#include<stdio.h>
#include<stdlib.h>
char total[50000] = {};
main() {
	char s[21];
	int a, b = 0;
	while(scanf("%s", s) == 1) {
		for(a = 0; s[a]; a++, b++)
			if(s[a] == 'E') break;
			else total[b] = s[a];
		if(s[a]) break;
	}
	int t1 = 0, t2 = 0;
	for(a = 0; a < b; a++) {
		if(total[a] == 'W') t1++;
		else t2++;
		if(t1 > 10 || t2 > 10) {
			if(abs(t1 - t2) > 1) {
				printf("%d:%d\n", t1, t2);
				t1 = 0, t2 = 0;
			}
		}
	}
	printf("%d:%d\n", t1, t2);
	t1 = 0, t2 = 0;
	puts("");
	for(a = 0; a < b; a++) {
		if(total[a] == 'W') t1++;
		else t2++;
		if(t1 > 20 || t2 > 20) {
			if(abs(t1 - t2) > 1) {
				printf("%d:%d\n", t1, t2);
				t1 = 0, t2 = 0;
			}
		}	
	}
	printf("%d:%d\n", t1, t2);
	return 0;
}
