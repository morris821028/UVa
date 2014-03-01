#include<stdio.h>
int gcd(int x, int y) {
	int t;
	while(x%y)
		t = x, x = y, y = t % y;
	return y;
}
main() {
	int T, n, A[101], Ans, t, a, b;
	char s[50000], g;
	scanf("%d", &T);
	getchar();
	while(T--) {
		gets(s), Ans = g = t = n= 0;
		for(a = 0; s[a]; a++) {
			if(s[a] <= '9' && s[a] >= '0')
				t = t*10 + s[a] - '0', g = 1;
			else {
				if(g)	A[n++] = t;
				t = 0, g = 0;
			}
		}
		if(g)	A[n++] = t;
		for(a = 0; a < n; a++)
			for(b = a+1; b < n; b++) {
				if(A[a] <= Ans || A[b] <= Ans) continue;
				t = gcd(A[a], A[b]);
				Ans = Ans > t ? Ans : t;
			}
		printf("%d\n", Ans);
	}
	return 0;
}
