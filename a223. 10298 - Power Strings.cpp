#include<stdio.h>
#include<string.h>
#define MaxL 1000001
int KMP_init(char *B) {
	int i, j;
	int P[MaxL];
	P[0] = -1, i = 1, j = -1;
	while(B[i]) {
		while(j >= 0 && B[j+1] != B[i])
			j = P[j];
		if(B[j+1] == B[i])
			++j;
		P[i] = j, ++i;
	}
	return j;
}
main() {
	char s[MaxL];
	while(gets(s)) {
		if(s[0] == '.' && s[1] == '\0')
			break;
		int n = strlen(s), t = KMP_init(s);
		if(n%(n-t-1) == 0)
			printf("%d\n", n/(n-t-1));
		else
			puts("1");
	}
	return 0;
}
