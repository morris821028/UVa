#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <map>
#include <iostream>
using namespace std;

inline int toIndex(int x) { // [0...36]
	if ('0' <= x && x <= '9')
		return x - '0';
	if ('A' <= x && x <= 'Z')
		return x + 10 - 'A';
	return 36;
}
int __mbuiltin_popcount(unsigned int x) {
	int v = 0;
	for (int i = 0; i < 32; i++)
		v += x&1, x >>= 1;
	return v;
}
const int MOD = 1874161; // 37^4
int FUZZY[MOD];
int main() {
	int C[16][16] = {};
	for (int i = 0; i < 16; i++) {
		C[i][0] = 1;
		for (int j = 1; j <= i; j++)
			C[i][j] = C[i-1][j-1] + C[i-1][j];
	}
	
	int testcase, n, m;	
	
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &n, &m);
		for (int i = 0; i < MOD; i++)
			FUZZY[i] = 0;
		int ret = 0;
		int same = 4 - m, diff = m;
		char s[8];
		for (int i = 0; i < n; i++) {
			scanf("%s", s);
			
			// find pair
			for (int j = 0; j < (1<<4); j++) {
				if (__mbuiltin_popcount(j) >= same) {
					int s1 = 0;
					for (int k = 0; k < 4; k++) {
						if ((j>>k)&1)
							s1 = s1 * 37 + toIndex(s[k]);
						else 
							s1 = s1 * 37 + toIndex('_');
					}
					int &r = FUZZY[s1];
					int v = __mbuiltin_popcount(j);
					if ((v - same)%2 == 0)
						ret += r * C[v][same];
					else
						ret -= r * C[v][same];
					r++;
				}
			}
		}
		printf("%d\n", ret);
	}
	return 0;
}
/*
1
6 2
ABCD
BC0D
DCAB
A5CF
ABFF
ABCB 
*/
