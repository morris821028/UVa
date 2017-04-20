#include <bits/stdc++.h>
using namespace std;

int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		uint32_t n;
		scanf("%u", &n);
		uint32_t ret = 0;
		for (int i = 0; i < 32; i++) {
			uint32_t m = (n<<i) | (n>>(32-i)); 
			m &= (1<<5)-1;
			ret |= 1U<<m;
		}
		puts(ret == UINT_MAX ? "yes" : "no");
	}
	return 0;
}

