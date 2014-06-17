#include <stdio.h>
#include <string.h>
struct Trie {
    bool n;
    int link[10];
} Node[200000];
int TrieSize;
int insertTrie(const char *str) {
    static int i, idx;
    idx = 0;
    for(i = 0; str[i]; i++) {
        if(!Node[idx].link[str[i]-'0']) {
            TrieSize++;
            memset(&Node[TrieSize], 0, sizeof(Node[0]));
            Node[idx].link[str[i]-'0'] = TrieSize;
        }
        idx = Node[idx].link[str[i]-'0'];
        if(Node[idx].n) {
            return 1;
        }
    }
    for(i = 0; i < 10; i++)
        if(Node[idx].link[i])
            return 1;
    Node[idx].n = true;
    return 0;
}
int main() {
    int t, n;
    char str[20];
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        getchar();
        TrieSize = 0;
        memset(&Node[0], 0, sizeof(Node[0]));
        int flag = 0;
        while(n--) {
            gets(str);
            if(flag)
                continue;
            flag = insertTrie(str);
        }
        if(flag)
            puts("NO");
        else
            puts("YES");
    }
    return 0;
}
