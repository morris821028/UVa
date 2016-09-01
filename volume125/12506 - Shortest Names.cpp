#include <stdio.h>
#include <string.h>
struct Trie {
    bool n;
    int link[26], cnt;
} Node[1048576];
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
        Node[idx].cnt++;
    }
    Node[idx].n = true;
    return 0;
}
long long ans;
void dfs(int nd, int dep) {
    int i;
    for(i = 0; i < 26; i++) {
        if(Node[nd].link[i]) {
            dfs(Node[nd].link[i], dep+1);
            if(Node[nd].cnt != 1 && Node[Node[nd].link[i]].cnt == 1)
                ans += dep;
        }
    }
}
char str[10000];
int main() {
    int t, n;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        TrieSize = 0;
        memset(&Node[0], 0, sizeof(Node[0]));
        while(n--) {
            scanf("%s", str);
            insertTrie(str);
        }
        ans = 0;
        dfs(0, 1);
        printf("%lld\n", ans);
    }
    return 0;
}
