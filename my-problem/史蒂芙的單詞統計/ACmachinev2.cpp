#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue>
#include <map>
#include <assert.h>
#define MAXNODE 1200000
#define MAXCHAR 62
using namespace std;
class ACmachine {
public:
    struct Node {
        Node *fail;
        map<char, Node*> next;
        int cnt, val;
        void init() {
            fail = NULL;
            cnt = val = 0;
            next.clear();
        }
    } nodes[MAXNODE];
    Node *root;
    int size;
    Node* getNode() {
    	assert(size < MAXNODE);
        Node *p = &nodes[size++];
        p->init();
        return p;
    }
    void init() {
        size = 0;
        root = getNode();
    }
	inline int toIndex(char c) {
		if (isdigit(c))	return c - '0' + 1;
		if (isupper(c)) return c - 'A' + 10 + 1;
		if (islower(c))	return c - 'a' + 26 + 10 + 1;
    }
    void insert(const char str[]) {
        Node *p = root;
        for (int i = 0, idx; str[i]; i++) {
            idx = toIndex(str[i]);
            if (!p->next.count(idx))
                p->next[idx] = getNode();
            p = p->next[idx];
        }
        p->cnt = 1;
    }
    void build() { // AC automation
        queue<Node*> Q;
        Node *u, *p;
        Q.push(root), root->fail = NULL;
        while (!Q.empty()) {
            u = Q.front(), Q.pop();
            for (int i = 0; i < MAXCHAR; i++) {
                if (!u->next.count(i))
                    continue;
                Q.push(u->next[i]);
                p = u->fail;
                while (p != NULL && !p->next.count(i))
                    p = p->fail;
                if (p == NULL)
                    u->next[i]->fail = root;
                else
                    u->next[i]->fail = p->next[i];
                u->next[i]->val = u->next[i]->fail->val + u->next[i]->cnt;
            }
        }
    }
    int query(const char str[]) {
        Node *u = root, *p;
        int matched = 0;
        for (int i = 0, idx; str[i]; i++) {
            idx = toIndex(str[i]);
            while (!u->next.count(idx) && u != root)
                u = u->fail;
            u = u->next.count(idx) ? u->next[idx] : NULL;
            u = (u == NULL) ? root : u;
            p = u;
            matched += p->val;
        }
        return matched;
    }
    void free() {
        return ;
        // owner memory pool version
        queue<Node*> Q;
        Q.push(root);
        Node *u;
        while (!Q.empty()) {
            u = Q.front(), Q.pop();
            for (int i = 0; i < MAXCHAR; i++) {
                if (u->next[i] != NULL) {
                    Q.push(u->next[i]);
                }
            }
            delete u;
        }
    }
};
ACmachine disk;
char s[1048576];
int main() {
    int n, m, cases = 0;
    while (scanf("%d", &n) == 1) {
        printf("Case #%d:\n", ++cases);
        disk.init();
        for (int i = 0; i < n; i++) {
        	scanf("%s", s);
        	disk.insert(s);
//        	fprintf(stderr, "%d\n", i);
        }
        disk.build();
        scanf("%d", &m);
        for (int i = 0; i < m; i++) {
        	scanf("%s", s);
        	int t = disk.query(s);
        	printf("%d\n", t);
        }
        disk.free();
    }
    return 0;
}
