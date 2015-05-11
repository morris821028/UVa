#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue>
#include <map>
#include <algorithm>
#define MAXCHAR 26 
#define MAXS (4096)
#define MAXNODE (1048576<<2)
#pragma comment( linker, "/STACK:1024000000,1024000000")
using namespace std;
class Trie {
public:
    struct Node {
        Node *next[MAXCHAR];
        int cnt;
        void init() {
            cnt = 0;
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
        }
        p->cnt += w;
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
char S[MAXS], buf[MAXS];
int main() {
	int n, m, q;
	while (scanf("%d", &n) == 1) {
		tool.init();
		for (int i = 0; i < n; i++) {
			scanf("%s", S);
			int m = strlen(S);
			sort(S, S+m);
			tool.insert(S, 1);
		}
		
		scanf("%d", &q);
		for (int i = 0; i < q; i++) {
			scanf("%d", &m);
			
			char letter[26][2];
			int val[26];
			for (int j = 0; j < m; j++)
				scanf("%s %d", letter[j], &val[j]);
				
			// brute
			int max_score = 0;
			for (int j = (1<<m)-1; j >= 0; j--) {
				int idx = 0, sum = 0;
				for (int k = 0; k < m; k++) {
					if ((j>>k)&1) 
						buf[idx++] = letter[k][0], sum += val[k];
				}
				buf[idx] = '\0';
				sort(buf, buf + idx);
				if (tool.find(buf))
					max_score = max(max_score, sum);
			}
			printf("%d\n", max_score);
		}
		tool.free();    
    }
    return 0;
}
/*

 */
