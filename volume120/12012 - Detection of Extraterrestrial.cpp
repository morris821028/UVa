#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

int kmpTable[1024];
void KMPtable(char *P, int len) {
    int i, j;
    kmpTable[0] = -1, i = 1, j = -1;
    while(i < len) {
        while(j >= 0 && P[j+1] != P[i])
            j = kmpTable[j];
        if(P[j+1] == P[i])
            j++;
        kmpTable[i++] = j;
    }
}
int main() {
	int testcase, cases = 0;
	char s[1024];
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%s", s);
		int n = strlen(s);
		int ret[1024] = {};
		for(int i = 0; i < n; i++) {
			KMPtable(s+i, n - i);
//			printf("%s\n", s+i);
//			for(int j = 0; j < n - i; j++)
//				printf("%d ", kmpTable[j]);
//			puts("");
			for(int j = 1; j <= n - i; j++) {
				if(j%(j - kmpTable[j-1] - 1) == 0) {
					int times = j / (j - kmpTable[j-1] - 1);
					for(int k = 1; k <= times; k++) {
						if(times%k == 0)
							ret[k] = max(ret[k], j);
					}
				}
			}
		}
		ret[1] = n;
		printf("Case #%d:", ++cases);
		for(int i = 1; i <= n; i++)
			printf(" %d", ret[i]);
		puts("");
	}
	return 0;
}
