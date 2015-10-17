#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <limits.h>
#include <string.h>

#define MAXN 262144
#define MAXS 1024
typedef struct Node {
    char A[MAXS+2];
    int size;
    struct Node *next, *prev;
} Node;
int midx = 0;
Node _mem[512];
extern inline void node_init(Node *u) {
    u->size = 0, u->next = u->prev = NULL;
}
extern inline void node_insert(Node *x, int pos, char val) {
    memmove(x->A+pos+1, x->A+pos, x->size-pos);
    x->A[pos] = val;
    x->size++;
}
extern inline void node_erase(Node *x, int pos) {
    memmove(x->A+pos, x->A+pos+1, x->size-pos);
    x->size--;
}
extern inline Node* newNode() {
    Node *p = &_mem[midx++];
    node_init(p);
    return p;
}
// UnrolledLinkedList
Node *head, *tail;
int PSIZE = MAXS;
Node* unrolled_init() {
    Node *head = newNode();
    head->size = 2, head->A[0] = '#', head->A[1] = '$';
    return tail = head;
}
char buf[MAXN], *bufptr;
void debug(Node *head) {
    bufptr = buf;
    Node *u = head;
    while (u != NULL) {
        memcpy(bufptr, u->A, u->size);
        bufptr += u->size;
        u = u->next;
    }
    *bufptr = '\0';
}
extern inline Node* mergeNode(Node *u, Node *v) {
    memcpy(u->A+u->size, v->A, v->size);
    u->next = v->next, u->size += v->size;
    if (v->next)    v->next->prev = u;
    else			tail = u;
    return u;
}
extern inline Node* splitNode(Node *u) {
    Node *v = newNode();
    int n = u->size>>1;
    memcpy(v->A, u->A+n, u->size-n);
    v->size = u->size - n, u->size = n;
	if (u->next)    u->next->prev = v;
    else            tail = v;
    v->next = u->next, u->next = v;
    v->prev = u;    
    return u;
}
extern inline void relaxList(Node *u, int dir) {
    if (dir == 1) {
        if (u->next != NULL && u->size + u->next->size < PSIZE) {
            mergeNode(u, u->next);
        } else if (u->size > PSIZE) {
            splitNode(u);
        }
    } else {
        if (u->prev != NULL && u->size + u->prev->size < PSIZE) {
            mergeNode(u->prev, u);
        } else if (u->size > PSIZE) {
            splitNode(u);
        }
    }
}
extern inline void erase(Node *ver, int pos) {
    Node *u = ver;
    u = ver;
    for (int l = 1, r; u; l = r+1, u = u->next) {
        r = l + u->size - 1;
        if (l <= pos && pos <= r) {
            node_erase(u, pos-l);
            relaxList(u, -1);
            relaxList(u, 1);
            return ;
        }
    }
}
extern inline void insert(Node *ver, int pos, char val) {
    Node *u = ver;
    for (int l = 1, r; u; l = r+1, u = u->next) {
        r = l + u->size - 1;
        if (l-1 <= pos && pos <= r) {
            node_insert(u, pos - l + 1, val);
            relaxList(u, 1);
            return ;
        }
    }
}
extern inline void rinsert(Node *u, char val) {
	node_insert(u, u->size-1, val);
	relaxList(u, 1);
}
extern inline void rerase(Node *u) {
	node_erase(u, u->size-2);
	relaxList(u, -1);
}
static int readtoken(char **ret) {
    static const int N = 1<<22;
    static char buf[1<<22];
    static char *end = buf, *token = NULL;
    if(token == NULL) {
        if((end = buf + fread(buf, 1, N, stdin)) == buf)
            return EOF;
        token = strtok(buf, " \n");
    } else {
        token = strtok(NULL, " \n");
    }
    *ret = token;
    return 1;
}
int main() {
    head = unrolled_init();
    char *cmd, *args[2];
    int n = 0;
    while (readtoken(&cmd) != EOF && cmd) {
        int pos = 0, x;
        if (cmd[0] == 'i') {
            readtoken(&args[0]);
            readtoken(&args[1]);
            if (args[0][0] == 'l') {
                insert(head, 1, args[1][0]);
            } else if (args[0][0] == 'r') {
                rinsert(tail, args[1][0]);
            } else {
                sscanf(args[0], "%d", &x);
                insert(head, x, args[1][0]);
            }
            n++;
        } else {
            readtoken(&args[0]);
            if (args[0][0] == 'l') {
                erase(head, 2);
            } else if (args[0][0] == 'r') {
            	rerase(tail);
            } else {
                sscanf(args[0], "%d", &x);
                erase(head, x+1);
            }
            n--;
        }
    }
    debug(head);
    char *s = buf+1;
    int cnt = 1, mx = 0;
    for (int i = 1; i <= n; i++) {
        if (s[i] == s[i-1]) {
            cnt++;
        } else {
            if (cnt > mx)
                mx = cnt;
            cnt = 1;
        }
    }
    cnt = 1;
    for (int i = 1; i <= n; i++) {
        if (s[i] == s[i-1]) {
            cnt++;
        } else {
            if (cnt == mx)
                printf("%c ", s[i-1]);
            cnt = 1;
        }
    }
    printf("%d\n", mx);
    return 0;
}
