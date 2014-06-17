#include <stdio.h>
#include <stdlib.h>

struct node {
    int v, c;
    node() {
        v = 0;
        c = 0;
    }
};
int cmp(const void *i, const void *j) {
    node *a, *b;
    a = (node *)i, b = (node *)j;
    if(a->v != b->v)
        return a->v - b->v;
    return b->c - a->c;
}
int main() {
    int i, j, flag = 0;
    char str[1005];
    while(gets(str)) {
        node I[128];
        for(i = 0; i < 128; i++)
            I[i].c = i;
        for(i = 0; str[i]; i++)
            I[str[i]].v++;
        for(i = 0, j = 0; i < 128; i++) {
            if(I[i].v) {
                I[j++] = I[i];
            }
        }
        if(flag++)
            puts("");
        qsort(I, j, sizeof(node), cmp);
        for(i = 0; i < j; i++)
            printf("%d %d\n", I[i].c, I[i].v);
    }
    return 0;
}
