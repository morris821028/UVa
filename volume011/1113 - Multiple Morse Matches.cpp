#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue>
#include <map>
#define MAXCHAR 2 
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
        return c == '.';
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
char S[MAXS], T[MAXS], buf[MAXS];
string morse[] = {
	".-", "-...", "-.-.", "-..",
	".", "..-.", "--.", "....",
	"..", ".---", "-.-", ".-..",
	"--", "-.", "---", ".--.",
	"--.-", ".-.", "...", "-",
	"..-", "...-", ".--", "-..-",
	"-.--", "--.."};
int main() {
    int testcase, n;
    scanf("%d", &testcase);
    while (testcase--) {
    	tool.init();
    	
    	scanf("%s", S);
    	scanf("%d", &n);    	
    	for (int i = 0; i < n; i++) {
    		scanf("%s", T);
    		int m = 0;
    		for (int j = 0; T[j]; j++)
    			for (int k = 0; morse[T[j] - 'A'][k]; k++)
					buf[m++] = morse[T[j] - 'A'][k];
			buf[m] = '\0';
			tool.insert(buf, 1);
    	}
    	
    	int len = (int) strlen(S);
    	int dp[MAXS] = {};
    	dp[0] = 1;
    	for (int i = 0; i < len; i++) {
    		Trie::Node *p = tool.root;
    		for (int j = i; j < len; j++) {
    			int u = tool.toIndex(S[j]);
    			if (p->next[u] == NULL)
					break;
				p = p->next[u];
				dp[j+1] += dp[i] * p->cnt;
    		}
    	}
    	
    	printf("%d\n", dp[len]);	
    	if (testcase)
    		puts("");
		
		tool.free();    
    }
    return 0;
}
/*

 */
