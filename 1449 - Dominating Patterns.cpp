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
    int who;
    Node() {
        fail = NULL;
        cnt = 0;
        who = 0;
        memset(next, 0, sizeof(next));
    }
};

void build_Trie(const char* str, Node *root, int who) {
    Node *p = root;
    int i = 0, idx;
    while(str[i]) {
        if(str[i] >= 'a' && str[i] <= 'z')
            idx = str[i] - 'a';
        if(p->next[idx] == NULL) {
            p->next[idx] = new Node();
        }
        p = p->next[idx];
        i++;
    }
    p->cnt++;
    p->who = who;
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
void query(const char* str, Node *root, int cnt[]) {
    int i = 0, idx;
    Node *tn, *p;
    tn = root;
    while(str[i]) {
        if(str[i] >= 'a' && str[i] <= 'z')
            idx = str[i] - 'a';
        while(tn->next[idx] == NULL && tn != root)
            tn = tn->fail;
        tn = tn->next[idx];
        tn = (tn == NULL) ? root : tn;
        p = tn;
        while(p != root) {
        	if(p->cnt > 0)
            	cnt[p->who]++;
            p = p->fail;
        }
        i++;
    }
}
char buf[1048576], pattern[256][256];
int main() {
    int n;
    while(scanf("%d", &n) == 1 && n) {
        Node *root = new Node();
        for(int i = 0; i < n; i++) {
        	scanf("%s", pattern[i]);
            build_Trie(pattern[i], root, i+1);
        }
        
        build_AC_automation(root);
        
        scanf("%s", buf);
        int cnt[256] = {};
        query(buf, root, cnt);
        free_AC_automation(root);
        int maxMatch = cnt[0];
        for(int i = 0; i < n; i++) {
        	maxMatch = max(maxMatch, cnt[i+1]);
        }
        printf("%d\n", maxMatch);
        for(int i = 0; i < n; i++) {
        	if(cnt[i+1] == maxMatch)
        		printf("%s\n", pattern[i]);
        }
    }
    return 0;
}
