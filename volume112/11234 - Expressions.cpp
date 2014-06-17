#include <stdio.h>
#include <string.h>
char post[10005], tree[10005];
int node[10005][2];
int idx, size;
void set(int nd) {
    tree[nd] = post[idx--];
    if(tree[nd] >= 'a' && tree[nd] <= 'z')
        return;
    node[nd][1] = ++size;
    set(size);
    node[nd][0] = ++size;
    set(size);
}
int main() {
    int t, i;
    scanf("%d", &t);
    gets(post);
    while(t--) {
        gets(post);
        idx = strlen(post)-1;
        size = 1;
        set(1);
        int qu[10005], qidx = 0;
        qu[0] = 1;
        for(i = 0; i <= qidx; i++) {
            if(tree[qu[i]] >= 'a' && tree[qu[i]] <= 'z')
                continue;
            qu[++qidx] = node[qu[i]][0];
            qu[++qidx] = node[qu[i]][1];
        }
        for(i = qidx; i >= 0; i--)
            putchar(tree[qu[i]]);
        puts("");
    }
    return 0;
}
