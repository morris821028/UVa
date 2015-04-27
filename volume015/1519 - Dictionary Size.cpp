#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm> 
#include <queue>
#include <map>
#define MAXCHAR 26
#define MAXS (1024)
#define MAXNODE (1048576)
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
	int chCnt[MAXCHAR]; // custom
    Node* getNode() {
        Node *p = &nodes[size++];
        p->init();
        return p;
    }
    void init() {
        size = cases = 0;
        root = getNode();
        memset(chCnt, 0, sizeof(chCnt));
    }
    inline int toIndex(char c) {
        return c - 'a';
    }
    // basis operation
    void insert(const char str[], int w) {
        Node *p = root;
        for (int i = 0, idx; str[i]; i++) {
            idx = toIndex(str[i]);
            if (p->next[idx] == NULL) {
                p->next[idx] = getNode();
                if (i)
                	chCnt[idx]++;
            }
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
} trie1, trie2;
/*
#different_prefix * #different_suffix - duplicate

duplicate example

prefix : Aaa, suffix : aaaB
then (Aaa)x(aaaB) AB, AaB, AaaB, ..., AaaaaaB
if use '*' => 3 * 4 = 12, there are only 6 str. overlap !!
(x+1) * (y+1) => x + y + 1, #duplicate = x * y
*/
int main() {
    int N;
	char s[MAXS];
    while (scanf("%d", &N) == 1 && N) {
    	trie1.init(), trie2.init();
    	
    	int sp[MAXCHAR] = {};
    	
    	for (int i = 0; i < N; i++) {
    		scanf("%s", s);
    
    		int len = strlen(s);
    		
    		trie1.insert(s, 1);
    		reverse(s, s + len);
    		trie2.insert(s, 1);
    		
    		if (len == 1)
    			sp[s[0] - 'a'] = 1;
    	}
    	long long ret = (long long) (trie1.size - 1) * (trie2.size - 1);
    	for (int i = 0; i < 26; i++)
    		ret -= (long long) trie1.chCnt[i] * trie2.chCnt[i];
    	for (int i = 0; i < 26; i++) // lost count string with single character
    		ret += sp[i];
    	printf("%lld\n", ret);
    	
    	trie1.free(), trie2.free();
    }
    return 0;
}
/*
3
abc
def
abef

1
a

2
a
b

2
ab
ba

3
a
a
a

 */
