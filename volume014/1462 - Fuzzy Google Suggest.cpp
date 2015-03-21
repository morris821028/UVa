#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue>
#include <map>
#define MAXCHAR 26
#define MAXS (1024)
#define MAXNODE (1048576<<2)
#pragma comment( linker, "/STACK:1024000000,1024000000")
using namespace std;
class Trie {
public:
    struct Node {
        Node *next[MAXCHAR];
        int cnt, label;
        void init() {
            cnt = label = 0;
            memset(next, 0, sizeof(next));
        }
    } nodes[MAXNODE];
    Node *root;
    int size, cases;
    Node* getNode() {
        Node *p = &nodes[size++];
        p->init();
        return p;
    }
    void init() {
        size = cases = 0;
        root = getNode();
    }
    inline int toIndex(char c) {
        return c - 'a';
    }
    // merge trie
    void merge_dfs(Node *p, Node *q) {
        for (int i = 0; i < MAXCHAR; i++) {
            if (q->next[i]) {
                Node *u = p->next[i], *v = q->next[i];
                if (u == NULL)
                    p->next[i] = getNode(), u = p->next[i];
                u->cnt += v->cnt;
                merge_dfs(u, v);
            }
        }
    }
    void merge(const Trie &other) {
        merge_dfs(root, other.root);
    }
    // basis operation
    void insert(const char str[], int w) {
        Node *p = root;
        for (int i = 0, idx; str[i]; i++) {
            idx = toIndex(str[i]);
            if (p->next[idx] == NULL)
                p->next[idx] = getNode();
            p = p->next[idx];
        	p->cnt += w;
        }
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
    // fuzzy find
    void fuzzy_dfs(Node *u, int idx, const char s[], int fuzzy_edit) {
    	if (fuzzy_edit < 0)			return ;
		if (u->label == cases + 1)	return ;
    	if (s[idx] == '\0') {
    		u->label = cases + 1;
    		return ;
		}
			
		if (u->label < cases)
			u->label = cases;
        for (int i = 0; i < MAXCHAR; i++) {
            if (u->next[i]) {
                if (toIndex(s[idx]) == i)
                	fuzzy_dfs(u->next[i], idx+1, s, fuzzy_edit);
                else
                	fuzzy_dfs(u->next[i], idx+1, s, fuzzy_edit-1); // replace s[idx]
                fuzzy_dfs(u->next[i], idx, s, fuzzy_edit-1); // insert s[idx]
            }
        }
		fuzzy_dfs(u, idx+1, s, fuzzy_edit-1); // delete s[idx]
    }
    int fuzzy_count(Node *u) {
    	if (u->label == cases+1)
    		return u->cnt;
    	if (u->label < cases)
    		return 0;
		int ret = 0;
        for (int i = 0; i < MAXCHAR; i++) {
            if (u->next[i])
                ret += fuzzy_count(u->next[i]);
        }
        return ret;
    }
    int fuzzyFind(const char str[], int fuzzy_edit) {
    	cases += 2;
    	fuzzy_dfs(root, 0, str, fuzzy_edit);
    	return fuzzy_count(root);
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
} tool;
char s[MAXS];
int main() {
    int N, Q, f;
    while (scanf("%d", &N) == 1 && N) {
    	tool.init();
    	while (getchar() != '\n');
    	
    	for (int i = 0; i < N; i++) {
    		gets(s);
    		tool.insert(s, 1);
    	}
    	scanf("%d", &Q);
    	for (int i = 0; i < Q; i++) {
    		scanf("%s %d", s, &f);
    		int ret = tool.fuzzyFind(s, f);
    		printf("%d\n", ret);
    	}
    	
    	tool.free();
    }
    return 0;
}
/*
4 
content 
common 
onganize 
case 
7 
c 0 
con 0 
con 2 
con 1 
com 1
comm 2 
cog 1
 */
