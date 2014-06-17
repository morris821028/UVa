#include <stdio.h>
const long long limit = 9876543210LL;
int Check(long long n) {
	char digit[10] = {0}, s[11], i = 0;
	sprintf(s, "%lld", n);
	while(s[i]) {
		digit[s[i]-'0']++;
		if(digit[s[i]-'0'] == 2)
			return 0;
		i++;
	}
	return 1;
}
int main() {
	int T;
	long long n, m, i;
	scanf("%d", &T);
	while(T--) {
		scanf("%lld", &n);
		for(i = 1; n*i <= limit; i++) {
			m = n*i;
			if(Check(i) && Check(m))
				printf("%lld / %lld = %lld\n", m, i, n);
		}
		if(T)	puts("");
	}
    return 0;
}
