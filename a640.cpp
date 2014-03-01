#include <stdio.h>
#include <vector>
#include <queue>
#include <iostream>
#include <string.h>
using namespace std;
struct Node {
    Node *next[20], *fail, *prev;
    int eos;//prefix has a string end
    int dp[20];
    int ASCII;
    Node() {
        fail = NULL, prev = NULL;
        memset(next, 0, sizeof(next));
        memset(dp, 0, sizeof(dp));
        eos = 0;
        ASCII = 0;
    }
};
void insertTrie(const int str[], Node *root, int label) {
    static Node *p;
    static int i, idx, eos;
    p = root, eos = 0;
    for(i = 0; str[i] > 0; i++) {
        idx = str[i];
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
        for(int i = 0; i < 20; i++) {
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
        for(int i = 0; i < 20; i++) {
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
void dp(Node *root, int len) {
    queue<Node*> Q;
    Node *nd, *p;
    root->dp[0] = 1;
    int k, i, j;
    int ans = 0, tot = 0;
    for(k = 0; k <= len; k++) {
        Q.push(root);
        ans = 0;
        while(!Q.empty()) {
            nd = Q.front(), Q.pop();
            for(i = nd->ASCII+1; i <= len; i++) {
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
                    if(p == NULL)
                        puts("NULL");
                    if(p->eos)
                        continue;//not safe
                    p->dp[k+1] += nd->dp[k];
                }
            }
            ans += nd->dp[k];
        }
        if(k >= 2)
            tot += ans;
    }
    if(tot == 0)
        puts("so sad");
    else
        printf("%d\n", tot);
}
int main() {
    int t, n, p;
    int x, A[20];
    int i, j, k;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &n, &p);
        Node *root = new Node();
        for(i = 0; i < p; i++) {
            scanf("%d", &x);
            for(j = 0; j < x; j++)
                scanf("%d", &A[j]);
            A[x] = -1;
            insertTrie(A, root, 1);
        }
        for(i = 1; i <= n; i++) {
            A[0] = i;
            A[1] = -1;
            insertTrie(A, root, 0);
        }
        buildACautomation(root);
        dp(root, n);
        freeTrie(root);
    }
    return 0;
}
