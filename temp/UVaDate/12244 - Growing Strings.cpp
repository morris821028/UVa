// advanced 1502 - GRE Words 
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue>
#include <map>
#include <algorithm>
#include <assert.h>
#include <assert.h>
#pragma comment( linker, "/STACK:1024000000,1024000000")
using namespace std;

const int MAXCHAR = 26;
const int MAXNODE = 1048576;

class ACmachine {
public:
    struct Node {
        Node *next[MAXCHAR], *fail;
        int cnt, val, id, nid;
        void init() {
            fail = NULL;
            cnt = val = 0;
            nid = id = -1;
            memset(next, 0, sizeof(next));
        }
    } nodes[MAXNODE];
    Node *root;
    int size;
    vector<int> fg[MAXNODE];
    Node* getNode() {
        Node *p = &nodes[size++];
        p->init(), p->nid = size-1;
        assert(size < MAXNODE);
        fg[p->nid].clear();
        return p;
    }
    void init() {
        size = 0;
        root = getNode();
    }
    int toIndex(char c) {
        return c - 'a';
    }
    void dfs(Node *p, Node *q) {
        for (int i = 0; i < MAXCHAR; i++) {
            if (q->next[i]) {
                Node *u = p->next[i], *v = q->next[i];
                if (u == NULL)
                    p->next[i] = getNode(), u = p->next[i];
                u->cnt |= v->cnt;
                dfs(u, v);
            }
        }
    }
    void merge(const ACmachine &other) {
        dfs(root, other.root);
    }
    void insert(const char str[], int sid) {
        Node *p = root;
        for (int i = 0, idx; str[i]; i++) {
            idx = toIndex(str[i]);
            if (p->next[idx] == NULL)
                p->next[idx] = getNode();
            p = p->next[idx];
        }
        p->cnt = 1;
        if (sid >= 0)	p->id = sid;
    }
    int find(const char str[]) {
        Node *p = root;
        for (int i = 0, idx; str[i]; i++) {
            idx = toIndex(str[i]);
            if (p->next[idx] == NULL)
                p->next[idx] = getNode();
            p = p->next[idx];
        }
        return p->cnt;
    }
    int build() { // AC automation    
        queue<Node*> Q;
        Node *u, *p;
        Q.push(root), root->fail = NULL;
        
        int ret = 0; // this problem
        while (!Q.empty()) {
            u = Q.front(), Q.pop();
            ret = max(ret, u->val); // this problem
            if (u != root) {
//            	assert(u->fail != NULL);
//            	assert(u->nid != u->fail->nid);
//            	fg[u->nid].push_back(u->fail->nid);
//            	fg[u->fail->nid].push_back(u->nid);
            }
            for (int i = 0; i < MAXCHAR; i++) {
                if (u->next[i] == NULL)
                    continue;
                Q.push(u->next[i]);
                p = u->fail;
                while (p != NULL && p->next[i] == NULL)
                    p = p->fail;
                if (p == NULL || p->next[i] == NULL)
                    u->next[i]->fail = root;
                else
                    u->next[i]->fail = p->next[i];
                // u->next[i]->val = u->next[i]->fail->val + u->next[i]->cnt;
                
                u->next[i]->val = max(u->next[i]->val, u->val);
                u->next[i]->val = max(u->next[i]->val, u->next[i]->fail->val) + u->next[i]->cnt;
                
                u->next[i]->id = u->next[i]->fail->id | u->next[i]->id;
            }
        }
        return ret; // this problem
    }
    int query(const char str[]) {
        Node *u = root, *p;
        int matched = 0;
        for (int i = 0, idx; str[i]; i++) {
            idx = toIndex(str[i]);
            while (u->next[idx] == NULL && u != root)
                u = u->fail;
            u = u->next[idx];
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

ACmachine ac;
char s[1024];
int main() {
	int N;
    while (scanf("%d", &N) == 1 && N) {	
       	ac.init();
       	
       	for (int i = 0; i < N; i++) {
       		scanf("%s", s);
       		ac.insert(s, i);
       	}
       	
       	int ret = ac.build(); // special
       	printf("%d\n", ret);
       	
        ac.free();
    }
    return 0;
}
/*
6 
plant 
ant 
cant 
decant 
deca 
an 

2 
supercalifragilisticexpialidocious 
rag 

0
 */


