#include <bits/stdc++.h> 
using namespace std;
class Trie {
public:
	static const int MAXN = 130000;
	static const int MAXC = 26;
	struct Node {
        Node *next[MAXC];
        void init() {
            memset(next, 0, sizeof(next));
        }
    } nodes[MAXN];
    Node *root;
    int size;
    Node* newNode() {
    	assert(size < MAXN);
        Node *p = &nodes[size++];
        p->init();
        return p;
    }
    void init() {
        size = 0;
        root = newNode();
    }
    inline int toIndex(char c) {
		return c - 'A';
    }
    inline int toChar(char c) {
		return c + 'A';
    }
    void insert(const char str[]) {
        Node *p = root;
        for (int i = 0, idx; str[i]; i++) {
            idx = toIndex(str[i]);
            if (p->next[idx] == NULL)
                p->next[idx] = newNode();
            p = p->next[idx];
        }
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
} tree;
char s[1024];
int main() {
	while (scanf("%s", s) == 1) {
		int n = strlen(s);
		tree.init();
		for (int i = 0; i < n; i++) {
			for (int j = i; j < n; j++) {
				char c = s[j+1];
				s[j+1] = '\0';
				tree.insert(s+i);
				s[j+1] = c;
			}
		}
		tree.print();
	}
	return 0;
}

