#include <stdio.h>
#include <string.h>
struct Trie {
    bool n;
    int link[26];
} Node[200000];
int TrieSize;
int insertTrie(const char *str) {
    static int i, idx;
    idx = 0;
    for(i = 0; str[i]; i++) {
        if(!Node[idx].link[str[i]-'a']) {
            TrieSize++;
            memset(&Node[TrieSize], 0, sizeof(Node[0]));
            Node[idx].link[str[i]-'a'] = TrieSize;
        }
        idx = Node[idx].link[str[i]-'a'];
    }
    if(Node[idx].n)
        return 1;
    Node[idx].n = true;
    return 0;
}
int main() {
    int n, flag;
    char str[25];
    while(scanf("%d", &n) == 1) {
        TrieSize = 0;
        memset(&Node[0], 0, sizeof(Node[0]));
        while(n--) {
            scanf("%s", str);
            insertTrie(str);
        }
        scanf("%d", &n);
        while(n--) {
            scanf("%s", str);
            flag = insertTrie(str);
            if(flag)    puts("yes");
            else    puts("no");
        }
    }
    return 0;
}
