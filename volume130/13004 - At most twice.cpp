#include <bits/stdc++.h>
using namespace std;

int main() {
	long long n;
	while (scanf("%lld", &n) == 1) {
		char buf[1024];
		sprintf(buf, "%lld", n);
		int cnt[16] = {};
		int len = strlen(buf);
		long long pre = 0;
		for (int i = 0; i < len; i++) {
			int ch = -1;
			for (int j = 9; j >= 0; j--) {
				if (cnt[j] == 2)	
					continue;
				cnt[j]++;
				int tlen = 0;
				long long mn = j, ten = 10;
				for (int k = 0; k < 10; k++) {
					for (int l = cnt[k]; l < 2; l++) {
						if (tlen < len-i-1) {
							mn = mn * 10 + k;
							tlen++, ten *= 10;
						}
					}
				}
				cnt[j]--;
				if (pre*ten + mn <= n) {
					ch = j;
					break;
				}
			}
			if (ch != -1)
				pre = pre*10 + ch, cnt[ch]++;
		}
		printf("%lld\n", pre);
	}
	return 0;
}
/*
1001223343
*/
