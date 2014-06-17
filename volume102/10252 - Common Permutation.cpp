#include <stdio.h>
int main() {
	char s[1001];
	while(gets(s)) {
		int count1[128] = {}, count2[128] = {};
		int i, j;
		for(i = 0; s[i]; i++)
			count1[s[i]]++;
		gets(s);
		for(i = 0; s[i]; i++)
			count2[s[i]]++;
		for(i = 0; i < 128; i++) {
			for(j = 0; j < count1[i] && j < count2[i]; j++)
				printf("%c", i);
		}
		puts("");
	}
    return 0;
}
