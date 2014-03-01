#include<stdio.h>
int Check(char *s) {
	int i, stack[200], idx = -1;
	for(i = 0; s[i]; i++) {
		switch(s[i]) {
			case '(':
				stack[++idx] = '(';
				break;
			case '[':
				stack[++idx] = '[';
				break;
			case ')':
				if(idx < 0)		return 0;
				if(stack[idx] == '(')	idx--;
				else	return 0;
				break;
			case ']':
				if(idx < 0)		return 0;
				if(stack[idx] == '[')	idx--;
				else	return 0;
				break;
		}
	}
	if(idx == -1)	return 1;
	return 0;
}
int main() {
	int T;
	char s[200];
	scanf("%d", &T);
	getchar();
	while(T--) {
		gets(s);
		if(Check(s) == 0) 
			puts("No");
		else
			puts("Yes");
	}
    return 0;
}
/*
3
([])
(([()])))
([()[]()])()
*/
