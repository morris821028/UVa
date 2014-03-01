#include<stdio.h>
main() {
	int T, a, b, n, m;
	char s[501];
	scanf("%d", &T);
	while(T--) {
		scanf("%d %d", &n, &m);
		int Map[502][502] = {}, Ans;
		for(a = 1; a <= n; a++) {
			scanf("%s", s);
			for(b = 1; b<= m; b++)
				Map[a][b] = s[b-1] - '0';
		}
		n++, m++, Ans = 0;
		for(a = 0; a <= n; a++)
			for(b = 0; b <= m; b++) {
				if(Map[a][b] == 0) {
					if(a-1 >= 0 && Map[a-1][b] == 1)
						Ans++;
					if(a+1 <= n && Map[a+1][b] == 1)
						Ans++;
					if(b-1 >= 0 && Map[a][b-1] == 1)
						Ans++;
					if(b+1 <= m && Map[a][b+1] == 1)
						Ans++;
				}
			}
		printf("%d\n", Ans);
	}
	return 0;
}
