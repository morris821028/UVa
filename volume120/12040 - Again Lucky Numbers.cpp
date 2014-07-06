// http://mypaper.pchome.com.tw/zerojudge/post/1324462879
// AC ¦Û°Ê¾÷ DP
#include <stdio.h>
#include <vector>
#include <queue>
#include <iostream>
#include <string.h>
using namespace std;
struct Node {
    Node *next[10], *fail, *prev;
    int eos;//prefix has a string end
    long long dp[105]; // [string length]
    int ASCII;
    Node() {
        fail = NULL, prev = NULL;
        memset(next, 0, sizeof(next));
        memset(dp, 0, sizeof(dp));
        eos = 0;
        ASCII = 0;
    }
};
void insertTrie(const char str[], Node *root, int label) {
    static Node *p;
    static int i, idx, eos;
    p = root, eos = 0;
    for(i = 0; str[i]; i++) {
        idx = str[i] - '0';
        if(p->next[idx] == NULL) {
            p->next[idx] = new Node();
            p->next[idx]->prev = p;
            p->next[idx]->ASCII = idx;
        }
        eos |= p->eos;
        p = p->next[idx];
        p->eos |= eos;
    }
    p->eos |= label;
}
void freeTrie(Node *root) {
    queue<Node*> Q;
    Node *nd;
    Q.push(root);
    while(!Q.empty()) {
        nd = Q.front(), Q.pop();
        for(int i = 0; i < 10; i++) {
            if(nd->next[i] != NULL)
                Q.push(nd->next[i]);
        }
        delete nd;
    }
}
void buildACautomation(Node *root) {
    queue<Node*> Q;
    Node *nd, *p;
    root->fail = NULL;
    Q.push(root);
    while(!Q.empty()) {
        nd = Q.front(), Q.pop();
        for(int i = 0; i < 10; i++) {
            if(nd->next[i] == NULL)
                continue;
            Q.push(nd->next[i]);
            p = nd->fail;
            while(p != NULL && p->next[i] == NULL)
                p = p->fail;
            if(p == NULL)
                nd->next[i]->fail = root;
            else {
                nd->next[i]->fail = p->next[i];
                nd->next[i]->eos |= p->next[i]->eos;//special for dp
            }
        }
    }
}
const int mod = 10000007;
long long dp(Node *root, int len) {
    queue<Node*> Q;
    Node *nd, *p;
    root->dp[0] = 1;
    int k, i, j;
    long long ans, ret = 0;
    for(k = 0; k <= len; k++) {
        Q.push(root);
        ans = 0;
        while(!Q.empty()) {
            nd = Q.front(), Q.pop();
            for(i = (k == 0); i < 10; i++) { // leading 0's are not allowed
                if(nd->next[i] != NULL) {
                    if(nd->next[i]->eos)
                        continue;//not safe
                    nd->next[i]->dp[k+1] += nd->dp[k];
                    nd->next[i]->dp[k+1] %= mod;
                    Q.push(nd->next[i]);
                } else {
                    p = nd;
                    while(p != root && p->next[i] == NULL)
                        p = p->fail;
                    p = p->next[i];
                    if(p == NULL) // error message
                        puts("NULL");
                    if(p->eos)
                        continue;//not safe
                    p->dp[k+1] += nd->dp[k];
                    p->dp[k+1] %= mod;
                }
            }
            ans += nd->dp[k];
            ans %= mod;
        }
        if(k == len) {
            ret += ans;
            ret %= mod;
        }
    }
    return ret;
}
int main() {
    int n, p, i;
    int cases = 0, testcase;
    char pattern[105], s[105];
    scanf("%d", &testcase);
    while(testcase--) {
        Node *root = new Node();
        scanf("%d %s", &n, pattern);
        insertTrie(pattern, root, 1);
        for(int i = 0; i < 10; i++) {
        	s[0] = i + '0', s[1] = '\0';
        	insertTrie(s, root, 0);
        }
        buildACautomation(root);
        long long ret = dp(root, n);
        freeTrie(root);
        if(n == 1 && strcmp("0", pattern))
        	ret++;
        printf("%lld\n", ret);
    }
    return 0;
}
/*
3
1 3
2 13
2 1

*/
