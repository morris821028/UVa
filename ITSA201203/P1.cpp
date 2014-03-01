#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
int main() {
	int DP[51][51] = {}, i, j, k;
	DP[0][0] = 1;
	for(i = 1; i <= 50; i++) {
		for(j = i; j <= 50; j++) {
			for(k = 1; k <= 50; k++)
				DP[j][k] += DP[j-i][k-1];
		}
	}
	int T;
	char s[100];
	scanf("%d", &T);
	getchar();
	while(T--) {
		gets(s);
		int Num[5], n = 0, tmp = 0, f = 0;
		for(i = 0; s[i]; i++) {
			if(s[i] >= '0' && s[i] <= '9')
				tmp = tmp*10 + s[i]-'0', f = 1;
			else {
				if(f == 1) {
					Num[n++] = tmp;
				}
				tmp = 0, f = 0;
			}
		}
		if(f)	Num[n++] = tmp;
		int p, q, r;
		if(n == 1) {
			p = Num[0], q = 0, r = 50;
		} else if(n == 2){
			p = Num[0], q = 0, r = Num[1];
		} else
			p = Num[0], q = Num[1], r = Num[2];
		int ans = 0;
		for(i = q; i <= r; i++)
			ans += DP[p][i];
		printf("%d\n", ans);
	}
    return 0;
}
