#include<stdio.h>
char Ans[2097152];
short w[20];
int At;
void doing(int l, int h, int dv, char s) {
	if(l < h) {
		int m = (l+h)/2;
		doing(l, m, dv+1, '0' + w[dv]);
		Ans[At++] = s, Ans[At++] = ' ';
		doing(m+1, h, dv+1, '0' + !w[dv]);
	}
}
main() {
	int s[21] = {1}, n, a;
	for(a = 1; a <= 20; a++)	s[a] = s[a-1]*2;
	while(scanf("%d", &n) == 1 && n) {
		for(a = 0; a < n; a++)	scanf("%hd", &w[a]);
		At = 0, doing(0, s[n]-1, 1, '0' + w[0]), Ans[At] = '\0';
		puts(Ans);
	}
	return 0;
}
