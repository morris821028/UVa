#include<stdio.h>
int main() {
	int ASCII[26] = {0}, N, i, j;
	char s[2000];
	scanf("%d", &N);
	getchar();
	while(N--) {
		gets(s);
		for(i = 0; s[i]; i++)
			switch(s[i]) {
				case 'a' ... 'z' : ASCII[s[i]-'a']++;break;
				case 'A' ... 'Z' : ASCII[s[i]-'A']++;break; 
			}
	}
	for(i = 0; i < 26; i++) {
		int max = 0;
		for(j = 0; j < 26; j++)
			if(ASCII[j] > max)
				max = ASCII[j];
		if(max == 0)	break;
		for(j = 0; j < 26; j++)
			if(ASCII[j] == max) {
				printf("%c %d\n", j+'A', ASCII[j]);
				ASCII[j] = 0;
				break;
			}
	}
    return 0;
}
