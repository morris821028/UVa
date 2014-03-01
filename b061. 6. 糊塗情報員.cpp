#include<stdio.h>
#define Maxv 2147483647
#define Minv -2147483647
int opera[52], num[52];
int Calc(int x, int op, int y) {
	switch(op) {
		case '+':return x+y;
		case '-':return x-y;
		case '*':return x*y;
	}
}
int Min(int x, int y) {
	if(x < y)	return x;
	return y;
}
int Max(int x, int y) {
	if(x > y)	return x;
	return y;
}
int DP(int n) {		
	int a, b, c, d, min, max;
	int t1, t2, t3, t4;
	int DPmin[52][52], DPmax[52][52];
	for(a = 0; a < n; a++)
		DPmin[a][a] = DPmax[a][a] = num[a];
	for(a = 1; a < n; a++)
		for(b= 0, c= a + b; c < n; b++, c++) {
			min = Maxv, max = Minv;
			for(d = b; d < c; d++) {
				t1 = Calc(DPmin[b][d], opera[d], DPmin[d+1][c]);
				t2 = Calc(DPmin[b][d], opera[d], DPmax[d+1][c]);
				t3 = Calc(DPmax[b][d], opera[d], DPmax[d+1][c]);
				t4 = Calc(DPmax[b][d], opera[d], DPmin[d+1][c]);
				min = Min(Min(Min(t1, t2), Min(t3, t4)), min);
				max = Max(Max(Max(t1, t2), Max(t3, t4)), max);
			}
			DPmin[b][c] = min;
			DPmax[b][c] = max;
		}
	return DPmax[0][n-1];
}
main() {
	char s[1001];
	while(scanf("%s", s) == 1) {
		int a, ot = 0, nt = 0, t =0;
		for(a = 0; s[a]; a++) {/*analysis*/
			if(s[a] >= '0' && s[a] <= '9')
				t = t*10 + s[a]-'0';
			else {
				num[nt++] = t;
				opera[ot++] = s[a];
				t = 0;
			}
		}
		num[nt++] = t;
		printf("%d\n", DP(nt));
	}
	return 0;
}
