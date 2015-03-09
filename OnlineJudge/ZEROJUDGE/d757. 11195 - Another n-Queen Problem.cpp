#include<stdio.h>
#include<stdlib.h>
int y_row[16], Ans;
void backtracking(int n, int y, int x, int slash1, int slash2) {
	if(y == n) {Ans++; return ;}
	
	int nowslash1 = slash1 >> y;
	int nowslash2 = slash2 >> (n-y-1);
	int judge = y_row[y] & x & nowslash1 & nowslash2;
	int xput;
	while(judge) {
		xput = judge & (-judge); /*lowbit*/
		backtracking(n, y+1, x^xput, slash1^(xput<<y), slash2^(xput<<(n-y-1)));
		judge ^= xput;
	}
}
main() {
	int n, C = 0, a, b;
	char s[16];
	while(scanf("%d", &n) == 1 && n) {
		for(a = 0; a < n; a++) {
			scanf("%s", s);
			y_row[a] = (1<<n)-1;
			for(b = 0; b < n; b++)
				if(s[b] == '*')
					y_row[a] ^= (1 << b);
		}
		Ans = 0;
		backtracking(n, 0, (1<<n)-1, (1<<(2*n-1))-1, (1<<(2*n-1))-1);
		printf("Case %d: %d\n", ++C, Ans);
	}
	return 0;
}
