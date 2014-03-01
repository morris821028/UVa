#include<stdio.h>
main() {
	int t, s, e, a, b, x, in, out, n;
	while(scanf("%d", &t) == 1) {
		scanf("%d %d", &s, &e);
		int time[1441] = {}, p[26] = {};
		int buy;
		char item[3];
		for(a = 0; a < t; a++) {
			scanf("%d %d %d %d", &x, &in, &out, &n);
			if(in < s) in = s;
			if(out > e) out =e;
			for(b = in; b <= out; b++)	time[b]++;
			while(n--) {
				scanf("%d %s", &buy, item);
				if(buy >= s && buy <= e)
					p[item[0] - 'A'] ++;
			}
		}
		int max = 0;
		for(a = s; a <= e; a++) {
			max = (max > time[a]) ? max : time[a];
		}
		printf("%d\n", max);
		for(a = s; a <= e+1; a++) {
			if(time[a] == max) {
				if(a != 0) {
					if(time[a] != time[a-1])
						printf("%d ", a);
				}
			}
			if(a != 0) {
				if(time[a-1] == max && time[a] != max)
					printf("%d ", a-1);
			}
		}
		puts(""), max = 0;
		for(a = 0; a < 26; a++)
			max = (max > p[a]) ? max : p[a];
		if(max == 0) puts("?");
		else {
			for(a = 0; a < 26; a++)
				if(p[a] == max)
					printf("%c ", a+'A');
			puts("");
		}
	}
	return 0;
}
