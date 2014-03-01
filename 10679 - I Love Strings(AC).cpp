#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue>
#include <map>
#define maxKind 52
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
        if(str[i] >= 'A' && str[i] <= 'Z')
            idx = str[i]-'A';
        else
            idx = str[i]-'a'+26;
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
        if(str[i] >= 'A' && str[i] <= 'Z')
            idx = str[i]-'A';
        else
            idx = str[i]-'a'+26;
        while(tn->next[idx] == NULL && tn != root)
            tn = tn->fail;
        tn = tn->next[idx];
        tn = (tn == NULL) ? root : tn;
        p = tn;
        while(p != root && p->cnt != -1) {
            /*
                cnt += p->cnt;
                p->cnt = 0;
            */
            cnt[p->who] = 1;
            p->cnt = -1;
            p = p->fail;
        }
        i++;
    }
}
char buf[100001];
int main() {
    int t, n;
    scanf("%d", &t);
    getchar();
    map<string, int> record;
    string S, T[1001];
    while(t--) {
        gets(buf);
        S = buf;
        scanf("%d", &n);
        record.clear();
        getchar();
        Node *root = new Node();
        int encode = 0;
        for(int i = 0; i < n; i++) {
            gets(buf);
            T[i] = buf;
            if(record[T[i]] == 0)
                record[T[i]] = ++encode;
            build_Trie(T[i].c_str(), root, record[T[i]]);
        }
        int cnt[1001] = {};
        build_AC_automation(root);
        query(S.c_str(), root, cnt);
        free_AC_automation(root);
        for(int i = 0; i < n; i++) {
            int num = record[T[i]];
            printf("%c\n", cnt[num] == 0 ? 'n' : 'y');
        }
    }
    return 0;
}
