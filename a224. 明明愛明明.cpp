#include<stdio.h>
main() {
	char s[1001];
	while(gets(s)) {
		int a, t[26] = {}, f = 0;
		for(a = 0; s[a]; a++)
			if(s[a] >= 'a' && s[a] <= 'z')
				t[s[a]-'a']++;
			else if(s[a] >= 'A' && s[a] <= 'Z')
				t[s[a]-'A']++;
		for(a = 0; a < 26; a++)
			f += t[a]&1;
		puts(f > 1 ? "no..." : "yes !");
	}
	return 0;
}
