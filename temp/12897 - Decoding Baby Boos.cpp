#include <stdio.h> 
#include <string.h>
using namespace std;
char s[1048576];
int main() {
	int testcase, n;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%s", s);
		scanf("%d", &n);
		
		char R[128], s1[10], s2[10];
		for (int i = 0; i < 128; i++)
			R[i] = i;
		for (int i = 0; i < n; i++) {
			scanf("%s %s", s1, s2);
			for (int j = 'A'; j <= 'Z'; j++)
				if (R[j] == s2[0])
					R[j] = s1[0];
		}
		
		for (int i = 0; s[i]; i++)
			putchar(R[s[i]]);
		puts("");
	}
	return 0;
}
/*
2
AVVU_TUMI_COLING_PARO_NAY
3
B V
D L
H Y
AABBCCY
3
A B
B C
C A
*/
