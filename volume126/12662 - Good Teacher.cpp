#include <stdio.h>
#include <string.h>

int main() {
	int n, q, x;
	char s[105][10];
	while(scanf("%d", &n) == 1) {
		for(int i = 1; i <= n; i++)
			scanf("%s", s[i]);
		scanf("%d", &q);
		while(q--) {
			scanf("%d", &x);
			if(strcmp(s[x], "?"))
				puts(s[x]);
			else {
				int l, r, p;
				l = r = 0;
				p = x - 1;
				while(p > 0 && !strcmp(s[p], "?"))
					p--, l++;
				if(p <= 0)	l = 0x3f3f3f;
				p = x + 1;
				while(p <= n && !strcmp(s[p], "?"))
					p++, r++;
				if(p > n)	r = 0x3f3f3f;
				l++, r++;
				if(l == r)
					printf("middle of %s and %s\n", s[x - l], s[x + r]);
				else if(l < r) {
					for(int j = 0; j < l; j++)
						printf("right of ");
					printf("%s\n", s[x - l]);
				} else {
					for(int j = 0; j < r; j++)
						printf("left of ");
					printf("%s\n", s[x + r]);
				}
			}
		}
	}
	return 0;
}
/*
10
A ? ? D ? ? ? H ? ?
4
3
8
6
10
*/
