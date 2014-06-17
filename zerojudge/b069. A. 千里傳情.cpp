#include<stdio.h>
#include<stdlib.h>
void transform(int n, char *A) {
	if(n == 0) return;
	transform(n/2, A-1);
	*A = (n&1) + '0';
}
main() {
	int k, test = 0, R, C, a, b, c;
	char s[500], *A;
	scanf("%d", &k), getchar();
	while(k--) {
		gets(s);
		R = 0, C = 0;
		for(a = 0; s[a]; a++)
			if(s[a] >= '0' && s[a] <= '9')
				R = R*10 + s[a] - '0';
			else break;
		for(a++; s[a]; a++)
			if(s[a] >= '0' && s[a] <= '9')
				C = C*10 + s[a] - '0';
			else break;
		A = s+a+1;
		char TF[2002], Ans[201][201];
		for(a = R*C-1; a >= 0; a--)	TF[a] = '0';
		TF[R*C] = '\0';
		for(a = 0; A[a]; a++)	transform(A[a] == ' ' ? 0 : (A[a]-'A'+1), TF+(a+1)*5-1);
		int x = 0, y = 0, p = 0, L = R*C, tr = R, tc = C;
		for(a = 0; a < L; ) {
			switch(p) {
				case 0:{
					for(b = 0; b < C; b++)
						Ans[x][y++] = TF[a++];
					y--, x++;
					R--, p = 1;break;
				}
				case 1:{
					for(b = 0; b < R; b++)
						Ans[x++][y] = TF[a++];
					y--, x--;
					C--, p = 2;break;
				}
				case 2:{
					for(b = 0; b < C; b++)
						Ans[x][y--] = TF[a++];
					y++, x--;
					R--, p = 3;break;
				}
				case 3:{
					for(b = 0; b < R; b++)
						Ans[x--][y] = TF[a++];
					y++, x++;
					C--, p = 0;break;
				}
			}
		}
		printf("%d ", ++test);
		for(a = 0; a < tr; a++) {
			for(b = 0; b < tc; b++)
				printf("%c", Ans[a][b]);
		}
		puts("");
	}
	return 0;
}
