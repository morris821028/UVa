#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
main() {
	int a, b;
	char s[300], edit[300];
	while(gets(s)) {
		gets(edit);
		int Ls = strlen(s), Le = strlen(edit);
		int index, t;
		for(a = 0; a < Le; a++) {
			switch(edit[a]) {
				case '0':index = 0;break;
				case '$':index = Ls;break;
				case 'x': {
					for(b = index; b < Ls-1; b++)
						s[b] = s[b+1];
					s[--Ls] = '\0';break;
				}
				case 's': {
					if(index < Ls-1)
						t = s[index], s[index] = s[index+1], s[index+1] = t;
					break;
				}
				case 'i': {
					for(b = Ls; b > index; b--)
						s[b] = s[b-1];
					s[index] = edit[++a], s[++Ls] = '\0', index++;
					break;
				}
				case 'u': {
					if(s[index] >= 'a' && s[index] <= 'z')
						s[index] = s[index] - 'a' + 'A';
					index++;
					break;
				}
				case '+':index++;break;
				case '-':index--;break;
			}
		}
		puts(s);
	}
	return 0;
}
