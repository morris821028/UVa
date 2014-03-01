#include<stdio.h>
int Priority(char c) {
	switch(c) {
		case '(':return 1;
		case ')':return 2;
		case '+':return 3;
		case '-':return 3;
		case '*':return 4;
		case '/':return 4;
		case '%':return 4;
	}
}
int change(char *A) {
	int i, j;
	int Ans[1000], Sign[1000], AIdx = -1, tmp, g;
	int Stack[1000], SIdx = -1;
	for(i = 0, tmp = 0, g = 0; A[i]; i++) {
		if(A[i] >= '0' && A[i] <= '9')
			tmp = tmp*10 + A[i]-'0', g = 1;
		else {
			if(g)
				Ans[++AIdx] = tmp, Sign[AIdx] = 0, tmp = 0, g = 0;
			Stack[++SIdx] = A[i];
			if(A[i] == ')') {
				SIdx--;
				while(SIdx >= 0 && Stack[SIdx] != '(')
					Ans[++AIdx] = Stack[SIdx], Sign[AIdx] = 1, SIdx--;
				SIdx--;
			}
			else
				while(SIdx >= 1 && Priority(Stack[SIdx-1]) >= Priority(Stack[SIdx]) && Stack[SIdx] != '(')
					Ans[++AIdx] = Stack[SIdx-1], Sign[AIdx] = 1, Stack[SIdx-1] = Stack[SIdx], SIdx--;
		}
	}
	if(g)
		Ans[++AIdx] = tmp, Sign[AIdx] = 0, tmp = 0, g = 0;
	while(SIdx >= 0)
		Ans[++AIdx] = Stack[SIdx], Sign[AIdx] = 1, SIdx--;
	for(i = 0; i <= AIdx; i++)
		if(Sign[i] == 1)
			printf("%c", Ans[i]);
		else
			printf("%d", Ans[i]);
	puts("");
}
main() {
	int t, C = 0;
	char s[1000], *A = s, tmp[3];
	scanf("%d", &t), getchar(), gets(tmp);
	while(t--) {
		A = s;
		while(gets(tmp)) {
			if(tmp[0] == '\0')	break;
			*A++ = tmp[0];
		}
		*A++ = '\0';
		change(s), puts("");
	}
	return 0;
}
