#include<stdio.h>
#include<string.h>
main() {
	int T, a, b;
	char s[101];
	scanf("%d" ,&T);
	while(T--) {
		scanf("%s", s);
		int L = strlen(s), L2 = L/2;
		for(a = 0, b = L-1; a <= L2; a++, b--)
			if(s[a] != s[b]) break;
		if(a == L2+1)
			puts("yes");
		else
			puts("no");
	}
	return 0;
}
