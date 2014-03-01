#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <queue>
using namespace std;
struct Node {
    Node *next[26];
    int label;
    Node() {
        label = 0;
        memset(next, 0, sizeof(next));
    }
};
void insertTrie(char s[], Node *root) {
    static Node *p;
    static int i, idx;
    p = root;
    for(i = 0; s[i]; i++) {
        idx = s[i]-'a';
        if(p->next[idx] == NULL)
            p->next[idx] = new Node();
        p = p->next[idx];
    }
    p->label = 1;
}
void freeTrie(Node *root) {
    static Node *p;
    static int i;
    queue<Node*> Q;
    while(!Q.empty()) {
        p = Q.front(), Q.pop();
        for(i = 0; i < 26; i++) {
            if(p->next[i] != NULL)
                Q.push(p->next[i]);
        }
        delete p;
    }
}
char word[300005], s[1005];
int dp[300005];
#define mod 20071027
int main() {
    int n, i, j;
    int cases = 0;
    while(scanf("%s", word+1) == 1) {
        scanf("%d", &n);
        Node *root = new Node();
        for(i = 0; i < n; i++) {
            scanf("%s", s);
            insertTrie(s, root);
        }
        int len = strlen(word+1);
        memset(dp, 0, sizeof(dp));
        dp[0] = 1;
        for(i = 0; i < len; i++) {
            Node *p = root->next[word[i+1]-'a'];
            for(j = i+1; p != NULL && j <= len; j++) {
                if(p->label) {
                    dp[j] += dp[i];
                    if(dp[j] >= mod)
                        dp[j] -= mod;
                }
                if(word[j+1] != '\0')
                    p = p->next[word[j+1]-'a'];
            }
        }
        printf("Case %d: %d\n", ++cases, dp[len]);
        freeTrie(root);
    }
    return 0;
}
/*
abcd
4
a
b
cd
ab
*/
