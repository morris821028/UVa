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
    return b->v - a->v;
}
int main() {
    int t, i;
    char str[10], a[10000], b[10000];
    scanf("%d", &t);
    gets(str);
    while(t--) {
        gets(str);
        gets(a);
        gets(b);
        node aI[128], bI[128];
        for(i = 0; i < 128; i++)
            aI[i].c = bI[i].c = i;
        for(i = 0; a[i]; i++)
            aI[a[i]].v++;
        for(i = 0; b[i]; i++)
            bI[b[i]].v++;
        qsort(aI, 128, sizeof(node), cmp);
        qsort(bI, 128, sizeof(node), cmp);
        int mapp[128] = {};
        for(i = 0; i < 128; i++) {
            mapp[bI[i].c] = aI[i].c;
        }
        for(i = 0; b[i]; i++)
            putchar(mapp[b[i]]);
        puts("");
        if(t)
            puts("");
    }
    return 0;
}
