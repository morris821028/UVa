#include <stdio.h>
#include <vector>
#include <queue>
#include <iostream>
#include <string.h>
using namespace std;
struct Node {
    Node *next[2], *fail, *prev;
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
// 'H' 1, 'T' 0
void insertTrie(const char str[], Node *root, int label) {
    static Node *p;
    static int i, idx, eos;
    p = root, eos = 0;
    for(i = 0; str[i]; i++) {
        idx = (str[i] == 'H');
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
        for(int i = 0; i < 2; i++) {
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
        for(int i = 0; i < 2; i++) {
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
long long gcd(long long a, long long b) {
    if(a == 0)  return b;
    if(b == 0)  return a;
    long long t;
    while(a%b)
        t = a, a = b, b = t%b;
    return b;
}
void dp(Node *root, int len) {
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
            for(i = 0; i < 2; i++) {
                if(nd->next[i] != NULL) {
                    if(nd->next[i]->eos)
                        continue;//not safe
                    nd->next[i]->dp[k+1] = nd->next[i]->dp[k+1] + nd->dp[k];
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
                }
            }
            ans += nd->dp[k];
        }
        if(k == len)
            ret += ans;
    }
    ans = 1LL<<len;// ret/ans
    long long g = gcd(ret, ans);
    ans /= g, ret /= g;
    if(ret == 0)
        puts("0");
    else
        printf("%lld/%lld\n", ret, ans);
}
int main() {
    int n, p, i;
    int cases = 0;
    char pattern[105];
    while(scanf("%d %d", &n, &p) == 2) {
        if(n == 0 && p == 0)
            break;
        Node *root = new Node();
        for(i = 0; i < p; i++) {
            scanf("%s", pattern);
            insertTrie(pattern, root, 1);
        }
        pattern[0] = 'H', pattern[1] = '\0';
        insertTrie(pattern, root, 0);
        pattern[0] = 'T', pattern[1] = '\0';
        insertTrie(pattern, root, 0);
        printf("Case %d: ", ++cases);
        buildACautomation(root);
        dp(root, n);
        freeTrie(root);
    }
    return 0;
}
