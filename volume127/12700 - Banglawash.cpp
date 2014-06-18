#include <stdio.h> 

int main() {
	char s[1024];
	int n, cases = 0;
	scanf("%*d");
	while(scanf("%d", &n) == 1) {
		scanf("%s", s);
		int c[128] = {};
		for(int i = 0; i < n; i++)
			c[s[i]]++;
		printf("Case %d: ", ++cases);
		if(c['B'] > 0 && c['W'] == 0 && c['T'] == 0)
			puts("BANGLAWASH");
		else if(c['W'] > 0 && c['B'] == 0 && c['T'] == 0)
			puts("WHITEWASH");
		else if(c['A'] == n)
			puts("ABANDONED");
		else if(c['B'] > c['W'])
			printf("BANGLADESH %d - %d\n", c['B'], c['W']);
		else if(c['B'] < c['W'])
			printf("WWW %d - %d\n", c['W'], c['B']);
		else
			printf("DRAW %d %d\n", c['W'], c['T']);
	}
	return 0;
}
/*
6
3
BBB
3
WWW
3
BWB
4
BWWT
3
BTW
2
AA
*/
