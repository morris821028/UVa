#include <stdio.h>
#include <string.h>
#include <vector>
#include <queue>
#include <iostream>
using namespace std;
string word[20000];
vector<int> Top10[100000];
struct Node {
    Node *next[26], *fail;
    vector<int> label;
    int matched;
    Node() {
        fail = NULL;
        matched = -1;
        label.clear();
        memset(next, 0, sizeof(next));
    }
};
void insertTrie(const char str[], Node *root, int label) {
    static Node *p;
    static int i, idx;
    p = root;
    for(i = 0; str[i]; i++) {
        idx = str[i]-'a';
        if(p->next[idx] == NULL) {
            p->next[idx] = new Node();
        }
        p = p->next[idx];
    }
    p->label.push_back(label);
}
void freeTrie(Node *root) {
    queue<Node*> Q;
    Node *nd;
    while(!Q.empty()) {
        nd = Q.front(), Q.pop();
        for(int i = 0; i < 26; i++)
            if(nd->next[i] != NULL)
                Q.push(nd->next[i]);
        nd->label.clear();
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
        for(int i = 0; i < 26; i++) {
            if(nd->next[i] == NULL)
                continue;
            Q.push(nd->next[i]);
            p = nd->fail;
            while(p != NULL && p->next[i] == NULL)
                p = p->fail;
            if(p == NULL)
                nd->next[i]->fail = root;
            else
                nd->next[i]->fail = p->next[i];
        }
    }
}
void quertACautomaiton(const char* str, Node *root, int number) {
    static Node *p, *q;
    static int i, idx;
    p = root;
    for(i = 0; str[i]; i++) {
        idx = str[i]-'a';
        while(p != root && p->next[idx] == NULL)
            p = p->fail;
        p = p->next[idx];
        p = (p == NULL) ? root : p;
        q = p;
        while(q != root && q->matched != number) {
            int bflag = 0;
            for(vector<int>::iterator it = q->label.begin();
                it != q->label.end(); it++) {
                if(Top10[*it].size() == 10) {
                    bflag = 1;
                    break;
                }
                Top10[*it].push_back(number);
            }
            if(bflag)   break;
            q->matched = number;
            q = q->fail;
        }
    }
}
void sortTrie(Node *root, Node *qroot) {
    // 1.shorter length 2. lexicographically 3. label small
    Node *tn;
    queue<Node*> Q;
    Q.push(root);
    while(!Q.empty()) {
        tn = Q.front(), Q.pop();
        for(int i = 0; i < 26; i++) {
            if(tn->next[i] == NULL)
                continue;
            Q.push(tn->next[i]);
        }
        for(vector<int>::iterator it = tn->label.begin();
            it != tn->label.end(); it++) {
            quertACautomaiton(word[*it].c_str(), qroot, *it);
            //cout << word[*it] << endl;
        }
    }
}
int main() {
    int n, m;
    int i, j;
    char s[100005];
    while(scanf("%d", &n) == 1) {
        while(getchar() != '\n');
        Node *root = new Node();
        for(i = 0; i < n; i++) {
            gets(s);
            word[i] = s;
            insertTrie(s, root, i);
        }
        scanf("%d", &m);
        while(getchar() != '\n');
        Node *qroot = new Node();
        for(i = 0; i < m; i++) {
            gets(s);
            insertTrie(s, qroot, i);
        }
        buildACautomation(qroot);
        sortTrie(root, qroot);
        for(i = 0; i < m; i++) {
            if(Top10[i].size() == 0)
                puts("-1");
            else {
                printf("%d", Top10[i][0]+1);
                for(j = 1; j < Top10[i].size(); j++)
                    printf(" %d", Top10[i][j]+1);
                puts("");
            }
            Top10[i].clear();
        }
        freeTrie(root);
        freeTrie(qroot);
    }
    return 0;
}
