#include <stdio.h>
#include <string.h>
const long long limit = 2147483647LL;
long long max(long long x, long long y) {
	return x > y ? x : y;
}
int main() {
	int t, i, j;
	char str[201];
	scanf("%d", &t);
	while(t--) {
		scanf("%s", str);
		int slen = strlen(str), i;
		long long DP[202] = {}, tmp = 0;
		for(i = 0; i < slen; i++) {
			if(str[i] == '0') {
				DP[i+1] = max(DP[i+1], DP[i]);
			} else {
				tmp = 0;
				for(j = i; j < slen; j++) {
					tmp = tmp*10 + str[j]-'0';
					if(tmp > limit)
						break;
					DP[j+1] = max(DP[j+1], DP[i]+tmp);
				}
			}
		}
		printf("%lld\n", DP[slen]);
	}
    return 0;
}
