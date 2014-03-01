#include<stdio.h>
char Map[502][502] = {};
short DP[502][502] = {};
short min(short x, short y) {
	if(x < y) return x; 
	return y; 
} 
int Calu_square(int n) {
	int a, b, Ans = 0;
	short t1, t2, t3;
	/*store (x,y) MaxL square¡A(x, y) is Lower right corner of the square*/
	for(a = 1; a <= n; a++)
		for(b = 1; b <= n; b++) {
			if(Map[a][b]) {
				t1 = 0, t2 = 0, t3 = 0; 
				if(Map[a-1][b-1])
					t1 = (DP[a-1][b-1] > 1) ? DP[a-1][b-1] : 1;
				if(Map[a][b-1])
					t2 = (DP[a][b-1] > 1) ? DP[a][b-1] : 1; 
				if(Map[a-1][b])
					t3 = (DP[a-1][b] > 1) ? DP[a-1][b] : 1;
				t1 = min(min(t1, t2), t3);	
				if(t1) { 
					DP[a][b] = t1+1;
					Ans += t1; 
				} 
				else DP[a][b] = 0;
			} 
		}
	return Ans; 
}
int Calu_rhombus(int n) {
	int a, b, c, Ans = 0;
	short t1, t2, t3;
	for(a = 1; a <= n; a++)
		for(c = a, b = 1; c >= 1; c--, b++) {
			if(Map[c][b]) {
				t1 = 0, t2 = 0, t3 = 0;
				if(Map[c-1][b-1])
					t1 = (DP[c-1][b-1] > 1) ? DP[c-1][b-1] : 1;
				if(b-2 > 0&& Map[c][b-2])
					t2 = (DP[c][b-2] > 1) ? DP[c][b-2] : 1; 
				if(Map[c+1][b-1])
					t3 = (DP[c+1][b-1] > 1) ? DP[c+1][b-1] : 1;
				t1 = min(min(t1, t2), t3);
				if(Map[c][b-1]) {
					DP[c][b] = t1+1;
					Ans += t1;
				}
				else DP[c][b] = 1;
			}
		}
	for(a = 2; a <= n; a++)
		for(c = n, b = a; c >= 1 && b <= n; c--, b++) {
			if(Map[c][b]) {
				t1 = 0, t2 = 0, t3 = 0;
				if(Map[c-1][b-1])
					t1 = (DP[c-1][b-1] > 1) ? DP[c-1][b-1] : 1;
				if(b-2 > 0&& Map[c][b-2])
					t2 = (DP[c][b-2] > 1) ? DP[c][b-2] : 1; 
				if(Map[c+1][b-1])
					t3 = (DP[c+1][b-1] > 1) ? DP[c+1][b-1] : 1;
				t1 = min(min(t1, t2), t3);	
				if(Map[c][b-1]) {
					DP[c][b] = t1+1;
					Ans += t1;
				}
				else DP[c][b] = 1;
			}
		}
	return Ans; 
} 
main() {
	int n, a, b;
	char s[501];
	while(scanf("%d", &n) == 1) {
		getchar();
		for(a = 0; a <= n+1; a++) 
			for(b = 0; b <= n+1; b++) 
				Map[a][b] = 0, DP[a][b] = 0; 
		for(a = 1; a <= n; a++) {
			gets(s);
			for(b = 1; b <= n; b++)
				Map[a][b] = (s[b-1] == 'x');/*x 1 . 0*/
		}
		printf("%d\n", Calu_rhombus(n)+Calu_square(n));
	}
	return 0;
}
