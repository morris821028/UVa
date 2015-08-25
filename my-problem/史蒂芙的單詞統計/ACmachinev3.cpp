#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue>
#include <map>
#include <assert.h>
#define MAXCHAR 62
#define MAXS (3000005)
#define MAXNODE 1200000
using namespace std;
class ACmachine {
public:
    struct Node {
    	vector<Node*> link;
        Node *fail;
        int cnt, val, base;
        Node() {
            fail = NULL;
            cnt = val = 0;
            base = 128, link = vector<Node*>(0, NULL);
        }
        Node* next(int c) {
        	if (c - base < 0)				return NULL;
        	if (c - base >= link.size())	return NULL;
        	return link[c - base];
        }
        void change(int c, Node *p) {
        	if (c >= base && c - base < link.size()) {
        		link[c-base] = p;
        	} else {
        		int nb = min(base, c), mx = max(base+(int)link.size()-1, c);
        		if (base == 128)	mx = c;
        		vector<Node*> co(mx-nb+1, NULL);
        		for (int i = 0; i < link.size(); i++)
        			co[i+base-nb] = link[i];
        		link = co, base = nb;
        		link[c-base] = p;
			}
        }
    } nodes[MAXNODE];
    Node *root;
    int size;
    Node* getNode() {
    	assert(size < MAXNODE);
        Node *p = &nodes[size++];
        *p = Node();
        return p;
    }
    void init() {
        size = 0;
        root = getNode();
    }
	inline int toIndex(char c) {
		if (isdigit(c))	return c - '0';
		if (isupper(c)) return c - 'A' + 10;
		if (islower(c))	return c - 'a' + 26 + 10;
    }
    void insert(const char str[]) {
        Node *p = root;
        for (int i = 0, idx; str[i]; i++) {
            idx = toIndex(str[i]);
            if (p->next(idx) == NULL)
                p->change(idx, getNode());
            p = p->next(idx);
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
                if (u->next(i) == NULL)
                    continue;
                Q.push(u->next(i));
                p = u->fail;
                while (p != NULL && p->next(i) == NULL)
                    p = p->fail;
                if (p == NULL)
                    u->next(i)->fail = root;
                else
                    u->next(i)->fail = p->next(i);
                u->next(i)->val = u->next(i)->fail->val + u->next(i)->cnt;
            }
        }
    }
    int query(const char str[]) {
        Node *u = root, *p;
        int matched = 0;
        for (int i = 0, idx; str[i]; i++) {
            idx = toIndex(str[i]);
            while (u->next(idx) == NULL && u != root)
                u = u->fail;
            u = u->next(idx);
            u = (u == NULL) ? root : u;
            p = u;
            matched += p->val;
        }
        return matched;
    }
    void free() {
        return ;
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
