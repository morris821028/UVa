#include <stdio.h>
#include <string.h>

#define MAXN 500<<1
#define MAXC 26
typedef struct Node {
    struct Node *next[MAXC], *pre;
    int step;
} Node;
Node *root, *tail;
Node _mem[MAXN];
int size;	
void init_node(Node *u) {
    u->pre = NULL, u->step = 0;
    memset(u->next, 0, sizeof(u->next));
}
Node* new_node() {
    Node *p = &_mem[size++];
    init_node(p);
    return p;
}
void init() {
    size = 0;
    root = tail = new_node();
}

int toIndex(char c) { return c - 'A'; }
char toChar(int c) { return c + 'A'; }
void add(char c, int len) {
    c = toIndex(c);
    Node *p, *q, *np, *nq;
    p = tail, np = new_node();
    np->step = len;
    for (; p && p->next[c] == NULL; p = p->pre)
        p->next[c] = np;
    tail = np;
    if (p == NULL) {
        np->pre = root;
    } else {
        if (p->next[c]->step == p->step+1) {
            np->pre = p->next[c];
        } else {
            q = p->next[c], nq = new_node();
            *nq = *q;
            nq->step = p->step + 1;
            q->pre = np->pre = nq;
            for (; p && p->next[c] == q; p = p->pre)
                p->next[c] = nq;
        }
    }
}
void build(const char *s) {
    init();
    for (int i = 0; s[i]; i++)
        add(s[i], i+1);
}
void dfs(Node *u, int idx, char path[]) {
    for (int i = 0; i < MAXC; i++) {
        if (u->next[i]) {
            path[idx] = toChar(i);
            path[idx+1] = '\0';
            puts(path);
            dfs(u->next[i], idx+1, path);
        }
    }
}
void print() {
    char s[1024];
    dfs(root, 0, s);
}

int main() {
    char s[1024];
    while (scanf("%s", s) == 1) {
        build(s);
        print();
    }
    return 0;
}
