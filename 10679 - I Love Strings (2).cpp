#include <stdio.h>
#include <string.h>
#include <queue>
#define rename(c) (c >= 'a' && c <= 'z' ? c-'a' : c-'A'+26)
using namespace std;
struct Node {
    Node *next[52], *fail;
    vector<int> label; // which word end.
    bool matched;
    Node() {
        fail = NULL;
        matched = false;
        label.clear();
        memset(next, 0, sizeof(next));
    }
};
void insert_Trie(char str[], Node *root, int label) {
    static Node *p;
    static int i, idx;
    p = root;
    for(i = 0; str[i]; i++) {
        idx = rename(str[i]);
        if(p->next[idx] == NULL) {
            p->next[idx] = new Node();
        }
        p = p->next[idx];
    }
    p->label.push_back(label);
}
void build_ACautomation(Node *root) {
    queue<Node*> Q;
    Node *nd, *p;
    root->fail = NULL;
    Q.push(root);
    while(!Q.empty()) {
        nd = Q.front(), Q.pop();
        for(int i = 0; i < 52; i++) {
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
void query_ACautonmation(char str[], Node *root, int exist_mark[]) {
    static Node *p, *q;
    static int i, idx;
    p = root;
    for(i = 0; str[i]; i++) {
        idx = rename(str[i]);
        while(p != root && p->next[idx] == NULL)
            p = p->fail;
        p = p->next[idx];
        p = (p == NULL) ? root : p;
        q = p;
        while(q != root && q->matched == false) {
            for(vector<int>::iterator it = q->label.begin();
                it != q->label.end(); it++) {
                exist_mark[*it] = 1;
            }
            q->matched = true;
            q = q->fail;
        }
    }
}
void free_ACautomation(Node *root) {
    queue<Node*> Q;
    Node *nd;
    while(!Q.empty()) {
        nd = Q.front(), Q.pop();
        for(int i = 0; i < 52; i++) {
            if(nd->next[i] != NULL)
                Q.push(nd->next[i]);
        }
        nd->label.clear();
        delete nd;
    }
}
char S[100005], T[1005];
int exist_mark[1005];
int main() {
    int t;
    scanf("%d", &t);
    getchar();
    int n, i;
    while(t--) {
        gets(S);
        scanf("%d", &n);
        getchar();
        Node *root = new Node();
        for(i = 0; i < n; i++) { // offline process
            gets(T);
            insert_Trie(T, root, i);
            exist_mark[i] = 0;
        }
        build_ACautomation(root);
        query_ACautonmation(S, root, exist_mark);
        for(i = 0; i < n; i++)
            puts(exist_mark[i] ? "y" : "n");
        free_ACautomation(root);
    }
    return 0;
}
