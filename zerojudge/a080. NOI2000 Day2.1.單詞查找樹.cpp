#include<stdio.h>
struct node {
	int ch[26];
}trie[32001];
main() {
	char s[64];
	int a, b, in = 0;
	while(scanf("%s", s) != EOF) {
		for(a = 0, b = 0; s[a]; a++) {
			if(trie[b].ch[s[a]-'A'] == 0) {
				in ++;
				trie[b].ch[s[a]-'A'] = in, b = in; 
			}
			else b = trie[b].ch[s[a]-'A']; 
		} 
	} 
	printf("%d\n", in + 1); 
	return 0; 
}

