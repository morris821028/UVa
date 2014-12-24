// http://mypaper.pchome.com.tw/zerojudge/post/1324462879
// AC ¦Û°Ê¾÷ DP
#include <stdio.h>
#include <vector>
#include <queue>
#include <iostream>
#include <string.h>
using namespace std;
#define MAXBRANCH 62
struct Node {
    Node *next[MAXBRANCH], *fail, *prev;
    int eos;//prefix has a string end
    double dp[105]; // [string length]
    int ASCII;
    Node() {
        fail = NULL, prev = NULL;
        memset(next, 0, sizeof(next));
        memset(dp, 0, sizeof(dp));
        eos = 0;
        ASCII = 0;
    }
};
int renameChar(char c) {
	if(c >= 'A' && c <= 'Z') return c - 'A';  
    if(c >= 'a' && c <= 'z') return c - 'a' + 26;  
    if(c >= '0' && c <= '9') return c - '0' + 52;
}
char invRenameChar(int i) {
	if (i < 26)	return 'A' + i;
	if (i < 52)	return 'a' + i - 26;
	return '0' + i - 52;
}
void insertTrie(const char str[], Node *root, int label) {
    static Node *p;
    static int i, idx, eos;
    p = root, eos = 0;
    for(i = 0; str[i]; i++) {
        idx = renameChar(str[i]);
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
        for(int i = 0; i < MAXBRANCH; i++) {
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
        for(int i = 0; i < MAXBRANCH; i++) {
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
double dp(Node *root, int L, double P[]) {
    queue<Node*> Q;
    Node *nd, *p;
    root->dp[0] = 1;
    int k, i, j;
    double ans, ret = 0;
    for(k = 0; k <= L; k++) {
        Q.push(root);
        ans = 0;
        while(!Q.empty()) {
            nd = Q.front(), Q.pop();
            for(i = 0; i < MAXBRANCH; i++) {
                if(nd->next[i] != NULL) {
                    if(nd->next[i]->eos)
                        continue;//not safe
                    nd->next[i]->dp[k+1] += nd->dp[k] * P[i];
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
                    p->dp[k+1] += nd->dp[k] * P[i];
                }
            }
            ans += nd->dp[k];
        }
        if(k == L) {
            ret += ans;
        }
    }
    return ret;
}
int main() {
    int n, m, L;
    int cases = 0, testcase;
    char pattern[105], s[105];
    scanf("%d", &testcase);
    while(testcase--) {
        Node *root = new Node();
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
        	scanf("%s", pattern);
        	insertTrie(pattern, root, 1);
    	}
        for(int i = 0; i < MAXBRANCH; i++) {
        	s[0] = invRenameChar(i), s[1] = '\0';
        	insertTrie(s, root, 0);
        }
        buildACautomation(root);
        
        double P[MAXBRANCH] = {}, p;
        scanf("%d", &m);
        for (int i = 0; i < m; i++) {
        	scanf("%s %lf", s, &p);
        	P[renameChar(s[0])] = p;
        }
        scanf("%d", &L);
        double ret = dp(root, L, P);
        printf("Case #%d: %.6lf\n", ++cases, ret);
        freeTrie(root);
    }
    return 0;
}
/*
2
1
a
2
a 0.5
b 0.5
2
2
ab
ab
2
a 0.2
b 0.8
2

*/
