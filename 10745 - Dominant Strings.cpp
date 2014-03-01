#include <stdio.h>
#include <string.h>
#include <set>
#include <iostream>
#include <queue>
using namespace std;
char s[15000][15];
int notclear[15000];
struct Node {
    Node *next[11];
    vector<int> label;
    Node() {
        label.clear();
        memset(next, 0, sizeof(next));
    }
};
void insertTrie(int str[], Node *root, int label) {
    static Node *p;
    static int i, idx;
    p = root;
    for(i = 0; i < 26; i++) {
        idx = str[i];
        if(p->next[idx] == NULL) {
            p->next[idx] = new Node();
        }
        p = p->next[idx];
    }
    p->label.push_back(label);
}
void clearTrie(int str[], Node *root) {
    static Node *p;
    static int i, idx;
    p = root;
    for(i = 0; i < 26; i++) {
        idx = str[i];
        if(p->next[idx] == NULL)
            return;
        p = p->next[idx];
    }
    for(vector<int>::iterator it = p->label.begin();
        it != p->label.end(); it++)
        notclear[*it] = 1;
    p->label.clear();
}
void freeTrie(Node *root) {
    queue<Node*> Q;
    Node *nd;
    while(!Q.empty()) {
        nd = Q.front(), Q.pop();
        for(int i = 0; i <= 10; i++) {
            if(nd->next[i] != NULL)
                Q.push(nd->next[i]);
        }
        nd->label.clear();
        delete nd;
    }
}
int cnt[26] = {}, cnt2[26];
Node *root = new Node();
set<string> R;
void dfs(int idx, int flag) {//backtrack Dominant
    if(idx == 26) {
        if(flag)
            clearTrie(cnt2, root);
        return ;
    }
    int i;
    for(i = 0; i <= cnt[idx]; i++) {
        cnt2[idx] = i;
        dfs(idx+1, flag|(i != cnt[idx]));
    }
}
void dfsfind(Node *p) {
    int i;
    for(i = 0; i < 11; i++)
        if(p->next[i] != NULL)
            dfsfind(p->next[i]);
    if(p->label.size() == 1)
        R.insert(s[p->label[0]]);
}
int main() {
    int n = 0, i, j;
    while(gets(s[n])) {
        //strlen(s) <= 10
        memset(cnt, 0, sizeof(cnt));
        for(i = 0; s[n][i]; i++)
            cnt[s[n][i]-'a']++;
        insertTrie(cnt, root, n);
        n++;
    }
    for(i = 0; i < n; i++) {
        if(!notclear[i]) {
            memset(cnt, 0, sizeof(cnt));
            for(j = 0; s[i][j]; j++)
                cnt[s[i][j]-'a']++;
            dfs(0, 0);
        }
    }
    dfsfind(root);
    freeTrie(root);
    for(set<string>::iterator it = R.begin();
        it != R.end(); it++)
        puts((*it).c_str());
    return 0;
}
/*
acmicpc
cccp
macpac
chimp
camp
*/
