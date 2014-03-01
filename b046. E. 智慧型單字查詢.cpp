#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct {
	char s[1000];
}STRING;
STRING S[1000], Ask[10];
main() {
	int C = 0, n, m, k, a, b, c, d, e;
	char cha;
	while(scanf("%d", &n) == 1) {
		for(a = 0; a < n; a++)
			scanf("%s", S[a].s);
		scanf("%d", &m);
		while(m--) {
			k = 0;
			while(scanf("%s%c", Ask[k].s, &cha) == 2 && cha != '\n')
				k++;
			int Ans[1000], find = 0, l1, l2, f1, f2;
			for(a = 0; a < n; a++) {
				for(b = 0; b <= k; b++) {
					l1 = strlen(Ask[b].s), l2 = strlen(S[a].s), f1 = 0, f2 = 0;
					if(Ask[b].s[0] == '*' && Ask[b].s[l1-1] == '*') {
						for(c = 0; c < l2; c++) {
							f1 = 0;
							for(d = c, e = 1; d < l2 && e < l1-1; d++, e++)
								if(Ask[b].s[e] != S[a].s[d])
									{f1 = 1;break;}
							if(e == l1-1 && f1 == 0)	{f2 = 1;break;}
						}
					} else if(Ask[b].s[0] == '*') {
						f1 = 0;
						for(c = l2-1, d = l1-1; c >= 0 && d >= 1; c--, d--)
							if(Ask[b].s[d] != S[a].s[c])
								{f1 = 1;break;}
						if(d == 0 && f1 == 0) {f2 = 1;}
					} else {
						f1 = 0;
						for(c = 0, d = 0; c < l2 && d < l1-1; c++, d++)
							if(Ask[b].s[d] != S[a].s[c])
								{f1 = 1;break;}
						if(d == l1-1 && f1 == 0) {f2 = 1;}
					}
					if(f2 == 0) break;
				}
				if(b == k+1)
					Ans[find++] = a;
			}
			printf("Query %d:", ++C);
			for(a = 0; a <= k; a++)	printf(" %s", Ask[a].s);
			printf(", %d item(s) is found.\n", find);
			for(a = 0; a < find; a++)
				printf("%s\n", S[Ans[a]].s);
			puts("");
		}
	}
	return 0;
}
