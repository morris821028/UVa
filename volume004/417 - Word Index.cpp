#include <stdio.h>
#include <string.h>

int main() {
	int i, j;
	int C[50][50] = {};
	C[0][0] = 1;
	for(i = 1; i < 50; i++) {
		C[i][0] = 1;
		for(j = 1; j <= i; j++)
			C[i][j] = C[i-1][j-1] + C[i-1][j];
	}
	char s[10];
	while(scanf("%s", &s) == 1) {
		int len = strlen(s), idx = 0;
		for(i = 1; i < len; i++) {
			if(s[i] < s[i-1]) {
				puts("0");break;
			}
			idx += C[26][i];
		}
		if(i != len)	continue;
		for(i = 0; i < len; i++) {
			for(j = (i == 0) ? 1 : s[i-1]-'a'+2; j <= s[i]-'a'; j++)
				idx += C[26-j][len-i-1];
		}
		printf("%d\n", idx+1);
	}
    return 0;
}
