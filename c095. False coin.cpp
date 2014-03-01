#include<stdio.h>
struct record {
	int l[101], r[101];
	char st[2];
}D[100];
main() {
	int m, n, k, a, b, c, pi, x;
	scanf("%d", &m);
	while(m--) {
		scanf("%d %d", &n, &k);
		int possible[101] = {};
		for(a = 0; a < k; a++) {
			for(b = 1; b <= n; b++) {
				D[a].l[b] = D[a].r[b] = 0;
			}
		}
		for(a = 0; a < k; a++) {
			scanf("%d", &pi);
			for(b = 0; b < pi; b++)	scanf("%d", &x), D[a].l[x] = 1;
			for(b = 0; b < pi; b++)	scanf("%d", &x), D[a].r[x] = 1;
			scanf("%s", &D[a].st);
			if(D[a].st[0] == '=') {
				for(b = 1; b <= n; b++) {
					if(D[a].l[b])	possible[b] = 1;
					if(D[a].r[b])	possible[b] = 1;
				}
			}
		}
		int Ans = 0, flag = 0, ll, lr, hl, hr;
		for(a = 1; a <= n; a++) {
			if(possible[a]) continue;
			for(b = 0; b < k; b++) {
				ll = lr = hl = hr = 0;
				if(D[b].l[a] != 0) ll--;
				if(D[b].r[a] != 0) lr--;
				if(D[b].l[a] != 0) hl++;
				if(D[b].r[a] != 0) hr++;
				if(ll == lr && D[b].st[0] == '=') continue;
				if(ll < lr && D[b].st[0] == '<') continue;
				if(ll > lr && D[b].st[0] == '>') continue;
				if(hl == hr && D[b].st[0] == '=') continue;
				if(hl < hr && D[b].st[0] == '<') continue;
				if(hl > hr && D[b].st[0] == '>') continue;
				break;
			}
			if(b == k)
				flag++, Ans = a;
		}
		if(flag == 1)	printf("%d\n", Ans);
		else puts("0");
		puts("");
	}
	return 0;
}
