#include <stdio.h>
#include <string.h>
#include <queue>
#include <algorithm>
using namespace std;
char T[1005][1005], P[105][105];
char M[1005][1005];
//<AC automation>
struct Node {
    Node *next[26], *fail;
    int matched, label;
    Node() {
        fail = NULL;
        matched = -1;
        label = -1;
        memset(next, 0, sizeof(next));
    }
};
int insertTrie(const char str[], Node *root, int label) {
    static Node *p;
    static int i, idx;
    p = root;
    for(i = 0; str[i]; i++) {
        idx = str[i]-'a';
        if(p->next[idx] == NULL)
            p->next[idx] = new Node();
        p = p->next[idx];
    }
    if(p->label == -1)
        p->label = label;
    return p->label;
}
void buildACautomation(Node *root) {
    queue<Node*> Q;
    Node *nd, *p;
    root->fail = NULL;
    Q.push(root);
    while(!Q.empty()) {
        nd = Q.front(), Q.pop();
        for(int i = 0; i < 26; i++) {
            if(nd->next[i] == NULL)
                continue;
            Q.push(nd->next[i]);
            p = nd->fail;
            while(p != NULL && p->next[i] == NULL)
                p = p->fail;
            if(p == NULL)
                nd->next[i]->fail = root;
            else
                nd->next[i]->fail = p->next[i];
        }
    }
}
void quertACautomaiton(const char* str, Node *root, int row) {
    static Node *p, *q;
    static int i, idx;
    p = root;
    for(i = 0; str[i]; i++) {
        idx = str[i]-'a';
        while(p != root && p->next[idx] == NULL)
            p = p->fail;
        p = p->next[idx];
        p = (p == NULL) ? root : p;
        q = p;
        M[row][i] = -1;
        if(q != root && q->label >= 0)
            M[row][i] = q->label;
    }
}
void freeTrie(Node *root) {
    queue<Node*> Q;
    Node *nd;
    while(!Q.empty()) {
        nd = Q.front(), Q.pop();
        for(int i = 0; i < 26; i++)
            if(nd->next[i] != NULL)
                Q.push(nd->next[i]);
        delete nd;
    }
}
//</AC automation>
int kmpTable[105];
void KMPtable(char *P, int len) {
    int i, j;
    kmpTable[0] = -1, i = 1, j = -1;
    while(i < len) {
        while(j >= 0 && P[j+1] != P[i])
            j = kmpTable[j];
        if(P[j+1] == P[i])
            j++;
        kmpTable[i++] = j;
    }
}
int KMPMatching(char T[], char P[], int tlen, int plen) {
    int i, j;
    int matchCnt = 0;
    for(i = 0, j = -1; i < tlen; i++) {
        while(j >= 0 && P[j+1] != T[i])
            j = kmpTable[j];
        if(P[j+1] == T[i])  j++;
        if(j == plen-1) {
            matchCnt++;
            j = kmpTable[j];
        }
    }
    return matchCnt;
}
int main() {
    int testcase;
    int n, m, x, y;
    int i, j, k;
    scanf("%d", &testcase);
    char pattern[105], str[1005];
    while(testcase--) {
        Node *root = new Node();
        scanf("%d %d", &n, &m);
        for(i = 0; i < n; i++)
            scanf("%s", T[i]);
        scanf("%d %d", &x, &y);
        for(i = 0; i < x; i++) {
            scanf("%s", P[i]);
            pattern[i] = insertTrie(P[i], root, i);
        }
        buildACautomation(root);
        for(i = 0; i < n; i++)
            quertACautomaiton(T[i], root, i);
        /*for(i = 0; i < x; i++)
            printf("%d xx\n", pattern[i]);
        for(i = 0; i < n; i++, puts(""))
            for(j = 0; j < m; j++)
                printf("%3d ", M[i][j]);*/
        KMPtable(pattern, x);
        int ret = 0;
        for(i = 0; i < m; i++) {
            for(j = 0; j < n; j++)
                str[j] = M[j][i];
            ret += KMPMatching(str, pattern, n, x);
        }
        printf("%d\n", ret);
        freeTrie(root);
    }
    return 0;
}
/*
3
1 1
x
1 1
y
3 3
abc
bcd
cde
2 2
bc
cd
3 3
aaa
aaa
aaa
2 2
aa
aa
*/
