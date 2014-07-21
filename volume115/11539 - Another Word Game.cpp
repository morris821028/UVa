#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue>
#include <map>
#define maxKind 26
using namespace std;

struct Node{
    Node *fail;
    Node *next[maxKind];
    int cnt;
    vector< pair<int, int> > attr;
    Node() {
        fail = NULL;
        cnt = 0;
        memset(next, 0, sizeof(next));
    }
};

void build_Trie(const char* str, Node *root, pair<int, int> val) {
    Node *p = root;
    int i = 0, idx;
    while(str[i]) {
        idx = str[i] - 'a';
        if(p->next[idx] == NULL)
            p->next[idx] = new Node();
        p = p->next[idx];
        i++;
    }
    p->cnt++;
    p->attr.push_back(val);
}
void build_AC_automation(Node *root) {
    root->fail = NULL;
    queue<Node*> Q;
    Q.push(root);
    Node *tn, *p;
    while(!Q.empty()) {
        tn = Q.front();
        Q.pop();
        for(int i = 0; i < maxKind; i++) {
            if(tn->next[i] == NULL)
                continue;
            Q.push(tn->next[i]);
            p = tn->fail;
            while(p != NULL && p->next[i] == NULL)
                p = p->fail;
            if(p == NULL)
                tn->next[i]->fail = root;
            else
                tn->next[i]->fail = p->next[i];
        }
    }
}
void free_AC_automation(Node *root) {
    queue<Node*> Q;
    Q.push(root);
    Node *tn, *p;
    while(!Q.empty()) {
        tn = Q.front();
        Q.pop();
        for(int i = 0; i < maxKind; i++) {
            if(tn->next[i] != NULL) {
                Q.push(tn->next[i]);
            }
        }
        free(tn);
    }
}
void query(const char* str, Node *root, int P) {
    Node *tn = root, *p;
    int n = strlen(str);
    int dp[100005] = {};
    for(int i = 0, idx; i < n; i++) {
        idx = str[i] - 'a';
        dp[i + 1] = dp[i] - P;
        while(tn->next[idx] == NULL && tn != root)
            tn = tn->fail;
        tn = tn->next[idx];
        tn = (tn == NULL) ? root : tn;
        p = tn;
        while(p != root) {
            if(p->cnt) {
            	for(vector< pair<int, int> >::iterator it = p->attr.begin();
					it != p->attr.end(); it++) {
					dp[i + 1] = max(dp[i + 1], dp[i - it->first + 1] + it->second);
				}
            }
            p = p->fail;
        }
    }
    printf("%d\n", dp[n]);
}
char buf[100001];
int main() {
    int testcase, N, P, val, cases = 0;
    scanf("%d", &testcase);
    while(testcase--) {
        Node *root = new Node();
        
        scanf("%d %d", &N, &P);
        for(int i = 0; i < N; i++) {
        	scanf("%s %d", buf, &val);
            build_Trie(buf, root, make_pair(strlen(buf), val));
        }
        
        build_AC_automation(root);
        scanf("%s", buf);
        printf("Case %d: ", ++cases);
        query(buf, root, P);
        free_AC_automation(root);
    }
    return 0;
}

