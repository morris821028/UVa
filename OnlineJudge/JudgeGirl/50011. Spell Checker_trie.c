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
    char *soff;
    struct Node *next[MAXCHAR];
} Node;
Node nodes[MAXNODE], *root;
char *output[MAXN];
char sbuf[MAXS], s[1024];
int outcnt = 0;
int size;
Node* get_node() {
    Node *p = &nodes[size++];
	p->soff = NULL;
    memset(p->next, 0, sizeof(p->next));
    return p;
}
void init() {
    size = 0;
    root = get_node();
}
void insert(char *str) {
	char *soff = str;
    Node *p = root;
    for (int idx; *str; str++) {
        idx = toIndex(*str);
        if (p->next[idx] == NULL)
            p->next[idx] = get_node();
        p = p->next[idx];
    }
    p->soff = soff;
}
int find(char *str) {
    Node *p = root;
    for (int idx; *str; str++) {
        idx = toIndex(*str);
        if (p->next[idx] == NULL)	return 0;
        p = p->next[idx];
    }
    return p->soff != NULL;
}
// fuzzy find

void fuzzy_dfs(Node *u, char *s, int fuzzy_edit) {
	if (*s == '\0') {
		if (u->soff)
			output[outcnt++] = u->soff;
    }
    if (*s && u->next[toIndex(*s)])
    	fuzzy_dfs(u->next[toIndex(*s)], s+1, fuzzy_edit);
    if (fuzzy_edit == 0)	return ;
    if (*s)
    	fuzzy_dfs(u, s+1, fuzzy_edit-1); // delete s[idx]
    for (int i = 0; i < MAXCHAR; i++) {
        if (u->next[i]) {
            fuzzy_dfs(u->next[i], s, fuzzy_edit-1); // insert s[idx]
        	if (*s && toIndex(*s) != i)
            	fuzzy_dfs(u->next[i], s+1, fuzzy_edit-1); // replace s[idx]
        }
    }
}
static int cmp(const void *a, const void *b) {
	return *(char **)a == *(char **)b ? 0 : (*(char **)a < *(char **)b ? -1 : 1);
}
void fuzzy_find(const char str[], int fuzzy_edit) {
	if (find(str)) {
		printf(">%s\n", str);
		return;
	}
	outcnt = 0;
	fuzzy_dfs(root, str, fuzzy_edit);
	if (outcnt == 0) {
		printf("!%s\n", str);
		return ;
	}
	qsort(output, outcnt, sizeof(char*), cmp);
	for (int i = 0; i < outcnt; i++) {
		if (i && output[i] == output[i-1])
			continue;
		putchar(i == 0 ? '?' : ' ');
		fputs(output[i], stdout);
	}
	printf("\n");
}
int main() {
    int N, Q, f;
    while (scanf("%d", &N) == 1 && N) {
    	init();
    	char *p = sbuf, *st;
    	for (int i = 0; i < N; i++) {
    		st = p, scanf("%s", p);
    		while (*p != '\0')
    			p++;
			p++, insert(st);
    	}
    	scanf("%d", &Q);
    	for (int i = 0; i < Q; i++) {
    		scanf("%s", s);
    		fuzzy_find(s, 1);
    	}
    }
    return 0;
}
