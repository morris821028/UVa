#include <stdio.h> 
#include <string.h>
#include <iostream>
#include <map>
#include <algorithm>
using namespace std;

int main() {
	int n;
	char s[128];
	while (scanf("%d", &n) == 1) {
		int mask[32] = {};
		for (int i = 0; i < n; i++) {
			scanf("%s", s);
			int x = 0;
			for (int j = 0; s[j]; j++)
				x ^= (1<<(s[j] - 'A')); 
			mask[i] = x;
		}
		
		// D&C, dp, bitmask
		map<int, int> dp1, dp2;
		int div1 = n/2, div2 = n - n/2;
		for (int i = 0; i < (1<<div1); i++) {
			int x = 0;
			for (int j = 0; j < div1; j++) {
				if ((i>>j)&1)
					x ^= mask[j];
			}
			if (dp1.count(x) || __builtin_popcount(dp1[x]) < __builtin_popcount(i))
				dp1[x] = i;			
		}
		for (int i = 0; i < (1<<div2); i++) {
			int x = 0;
			for (int j = 0; j < div2; j++) {
				if ((i>>j)&1)
					x ^= mask[j + div1];
			}
			if (dp2.count(x) || __builtin_popcount(dp2[x]) < __builtin_popcount(i))
				dp2[x] = i;			
		}
		
		int retCnt = 0, retMask = 0;
		for (map<int, int>::iterator it = dp1.begin();
			it != dp1.end(); it++) {
			if (dp2.count(it->first)) {
				int x = it->second | ((dp2[it->first]) << div1);
				if (__builtin_popcount(x) > retCnt) {
					retCnt = __builtin_popcount(x);
					retMask = x;
				}
			}
		}
		printf("%d\n", retCnt);
		for (int i = 0, f = 0; i < n; i++) {
			if ((retMask>>i)&1) {
				if (f)	putchar(' ');
				f = 1;
				printf("%d", i+1);
			}
		}
		puts("");
	}
	return 0;
}
