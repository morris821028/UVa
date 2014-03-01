#include<stdio.h>
#include<string.h>
main() {
	int n, k, a, b, c, A[201], Cycle[201];
	char s[201], Ans[201];
	while(scanf("%d", &n) == 1 && n) {		
		for(a = 1; a <= n; a++)
			scanf("%d", &A[a]);
		while(scanf("%d", &k) == 1 && k) {

			getchar(), gets(s);
			
			int L = strlen(s), cnt, t, pos;
			
			for(a = L; a < n; a++) s[a] = ' ';
			
			for(a = 1; a <= n; a++) {
				t = A[a];
				cnt = 1;
				while(a != t) {
					cnt++, t = A[t];
				}
				Cycle[a] = cnt;
			}
			for(a = 1; a <= n; a++) {
				pos = a;
				for(b = 0, c = k%Cycle[a]; b < c; b++)
					pos = A[pos];
				Ans[pos-1] = s[a-1];
			}
			Ans[n] = '\0';
			puts(Ans);
		}
		puts("");
	}
	return 0;
}
