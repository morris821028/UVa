#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <map>
#include <iostream>

using namespace std;
int toIndex(int x) { // [0...36]
	if ('0' <= x && x <= '9')
		return x - '0';
	if ('A' <= x && x <= 'Z')
		return x + 10 - 'A';
	return 36;
}
int main() {
	int testcase, n, m;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &n, &m);
		map< int, map<int, int> > FUZZY[1<<4];
		map< int, int > CNT[1<<4];
		int ret = 0;
		char s[8], s2[8], s3[8];
		int same = 4 - m, diff = m;
		for (int i = 0; i < n; i++) {
			scanf("%s", s);
			
			// find pair
			for (int j = 0; j < (1<<4); j++) {
				if (__builtin_popcount(j) == same) {
					int sidx1 = 0, sidx2 = 0;
					int s1 = 0, s3 = 0;
					for (int k = 0; k < 4; k++) {
						if ((j>>k)&1)
							s1 = s1 * 37 + toIndex(s[k]);
						else 
							s2[sidx2++] = s[k];
					}
										
					map<int, int> &tfuzzy = FUZZY[j][s1];
					int tot = CNT[j][s1], similar = 0;
					CNT[j][s1]++;
					
					for(int k = (1<<diff)-1; k > 0; k--) {
						s3 = 0;
						for (int p = 0; p < diff; p++) {
							if ((k>>p)&1)
								s3 = s3 * 37 + toIndex(s2[p]);
							else
								s3 = s3 * 37 + toIndex('_');
						}
						if (__builtin_popcount(k)%2 == 0)
							similar -= tfuzzy[s3];
						else
							similar += tfuzzy[s3];
						
						tfuzzy[s3]++;
					}
					
					ret += tot - similar;
//					printf("%d -- %d %d\n", tot - similar, tot, similar);
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
