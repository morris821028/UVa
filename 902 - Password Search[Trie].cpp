#include <stdio.h>
#include <string.h>

char str[1000000];
struct Trie {
    int n;
    int link[26];
} Node[2000000];
int TrieSize;
void insertTrie(const char* str) {
	static int i, idx;
	idx = 0;
	for(i = 0; str[i]; i++) {
		if(Node[idx].link[str[i]-'a'] == 0) {
			TrieSize++;
			memset(&Node[TrieSize], 0, sizeof(Node[0]));
			Node[idx].link[str[i]-'a'] = TrieSize;
		}
		idx = Node[idx].link[str[i]-'a'];
	}
	Node[idx].n ++;
}
int ans = 0, n;
char ansArr[20];
void travelTrie(char *str, int idx) {
    if(Node[idx].n > ans) {
        *str = '\0';
        memcpy(ansArr, str-n, n);
        ans = Node[idx].n;
    }
    for(int i = 0; i < 26; i++) {
        if(Node[idx].link[i] != 0) {
            *str = i+'a';
            travelTrie(str+1, Node[idx].link[i]);
        }
    }
}
int main() {
    int i;
    while(scanf("%d %s", &n, str) == 2) {
        int len = strlen(str);
        char ch;
        TrieSize = 0;
        memset(&Node[0], 0, sizeof(Node[0]));
        ans = 0;
        for(i = n; i <= len; i++) {
            ch = str[i];
            str[i] = '\0';
            insertTrie(str+i-n);
            str[i] = ch;
        }
        memset(ansArr, 0, sizeof(ansArr));
        travelTrie(str, 0);
        printf("%s\n", ansArr);
    }
    return 0;
}
