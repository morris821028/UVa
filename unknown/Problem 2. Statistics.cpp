#include<stdio.h>
#include<string.h>
main() {
	char s[1000], s1[15] = "\" ,;.[]?!()-?\"", flag = 0;
	while(gets(s)) {
		int a, b, l = strlen(s);
		for(a = 0; s1[a]; a++)
			if(s[a] != s1[a]) break;
		if(l == 14 && a == 14 && flag != 0) {
			printf("Ans\n");
			continue;
		}
		printf("%d %d\n", l, a);
		flag = 1;
	}
	return 0;
}
