#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXCHAR 26
#define MAXN 131072
#define MAXS 1048576
#define MAXNODE 1048576
#define toIndex(c) (c - 'a')
#define toChar(c) (c + 'a')
typedef struct Node {
    int cnt;
    struct Node *next[MAXCHAR];
} Node;
static Node nodes[MAXNODE], *root;
static int size;
Node* get_node() {
    Node *p = &nodes[size++];
	p->cnt = 0;
    memset(p->next, 0, sizeof(p->next));
    return p;
}
void init() {
    size = 0;
    root = get_node();
}
void insert(char *str) {
    Node *p = root;
    for (int idx; *str; str++) {
        idx = toIndex(*str);
        if (p->next[idx] == NULL)
            p->next[idx] = get_node();
        p = p->next[idx];
    }
    p->cnt++;
}
// fuzzy find
static int N, Q, L;
static int ret = 0;
void fuzzy_find(Node *u, char *s, int fuzzy_edit, int dep) {
	if (dep == L) {
		if (fuzzy_edit == 1)
			ret += u->cnt;
		else
			ret += u->cnt * L;
		return ;
	}
	if (fuzzy_edit == 1) {
		if (u->next[toIndex(*s)])
			fuzzy_find(u->next[toIndex(*s)], s+1, fuzzy_edit, dep+1);
	} else {
		for (int i = 0; i < MAXCHAR; i++) {
			if (u->next[i] == NULL)
				continue;
			fuzzy_find(u->next[i], s+1, fuzzy_edit+(toIndex(*s) != i), dep+1);
		}
	}
}
int main() {
	static char s[131072];
    while (scanf("%d %d %d", &N, &Q, &L) == 3) {
    	init();
    	for (int i = 0; i < N; i++) {
    		scanf("%s", s);
    		insert(s);
		}
		
		for (int i = 0; i < Q; i++) {
			scanf("%s", s);
			ret = 0;
			fuzzy_find(root, s, 0, 0);
			printf("%d\n", ret);
		}
	}
    return 0;
}
/*
3  1  3
aab
aba
aaa
aaa
*/

