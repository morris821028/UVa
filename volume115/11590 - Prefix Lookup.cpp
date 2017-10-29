#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h> 
using namespace std;

#define MAXCHAR 2
#define MAXNODE (32768*32)
class Trie {
public:
    struct Node {
        Node *next[MAXCHAR];
        int64_t cnt;
		int eof;
        void init() {
            cnt = eof = 0;
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
        return c - '0';
    }
    void insert(const char str[]) {
        Node *p = root;
        for (int i = 0, idx; str[i]; i++) {
            idx = toIndex(str[i]);
            if (p->next[idx] == NULL)
                p->next[idx] = getNode();
            p = p->next[idx];
        }
        p->eof = 1;
    }
    void dfs(Node *u, int m) {
    	if (m == 0) {
    		u->cnt = 1;
    		return ;
		}
		u->cnt = 0;
    	for (int i = 0; i < MAXCHAR; i++) {
    		if (u->next[i] != NULL) {
    			dfs(u->next[i], m-1);
    			if (u->next[i]->eof == 0)
    				u->cnt += u->next[i]->cnt;
    		} else {
    			u->cnt += 1LL<<(m-1);
    		}
		}
	}
    void suffix(int m) {
    	dfs(root, m);
	}
	int64_t prefix(const char str[]) {
		Node *p = root;
		for (int i = 0, idx; str[i]; i++) {
            idx = toIndex(str[i]);
            if (p->next[idx] == NULL)
                return 0;
            p = p->next[idx];
        }
        return p->cnt;
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
} tool;

inline int readchar() {
    const int N = 1048576;
    static char buf[N];
    static char *p = buf, *end = buf;
    if(p == end) {
        if((end = buf + fread(buf, 1, N, stdin)) == buf) return EOF;
        p = buf;
    }
    return *p++;
}
inline int ReadInt(int *x) {
    static char c, neg;
    while((c = readchar()) < '-')    {if(c == EOF) return 0;}
    neg = (c == '-') ? -1 : 1;
    *x = (neg == 1) ? c-'0' : 0;
    while((c = readchar()) >= '0')
        *x = (*x << 3) + (*x << 1) + c-'0';
    *x *= neg;
    return 1;
}
int main() {
	int n, m, q;
	char s[128], *ptr;
//	while (scanf("%d %d", &n, &m) == 2 && n) {
	while (ReadInt(&n) && ReadInt(&m), n) {
		tool.init();
		for (int i = 0; i < n; i++) {
			ptr = s;
			while ((ptr[0] = readchar()) < '*');
			ptr++;
			if (s[0] != '*') {
				while ((ptr[0] = readchar()) != '*')
					ptr++;
				ptr[0] = '\0';
			} else {
				s[0] = '\0';
			}
//			scanf("%s", s);
//			s[strlen(s)-1] = '\0';
			tool.insert(s);
		}
		tool.suffix(m);
//		scanf("%d", &q);
		ReadInt(&q);
		for (int i = 0; i < q; i++) {
			ptr = s;
			while ((ptr[0] = readchar()) < '*');
			ptr++;
			if (s[0] != '*') {
				while ((ptr[0] = readchar()) != '*')
					ptr++;
				ptr[0] = '\0';
			} else {
				s[0] = '\0';
			}
//			scanf("%s", s);
//			s[strlen(s)-1] = '\0';
			int64_t ret = tool.prefix(s);
			printf("%lld\n", ret);
		}
		puts("");
	}
	return 0;
}
/*
4 4
0*
11*
011*
1110*
5
*
0*
11*
011*
1110*

4 32
0*
11*
011*
1110*
5
*
0*
11*
011*
1110*

0 0 
*/
