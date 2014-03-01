#include <stdio.h>
struct Node {
    int l, r, p, v, x;
} node[1000];
int main() {
    int t = 0, rt, x;
    while(scanf("%d", &rt) == 1) {
        if(rt == -1)    break;
        printf("Case %d:\n", ++t);
        int size = 1, idx = 0;
        node[0].v = rt;
        node[0].l = node[0].r = 0;
        node[0].p = -1;
        node[0].x = 0;
        int minx = 0, maxx = 0;
        while(scanf("%d", &x) == 1) {
            if(node[idx].l == 0) {
                size++;
                node[idx].l = size;
                node[size].v = x;
                node[size].l = node[size].r = 0;
                node[size].p = idx;
                if(x != -1) {
                    node[size].x = node[idx].x-1;
                    idx = size;
                    if(node[size].x < minx)
                        minx = node[size].x;
                }
            } else if(node[idx].r == 0) {
                size++;
                node[idx].r = size;
                node[size].v = x;
                node[size].l = node[size].r = 0;
                node[size].p = idx;
                if(x != -1) {
                    node[size].x = node[idx].x+1;
                    idx = size;
                    if(node[size].x > maxx)
                        maxx = node[size].x;
                }
            }
            while(1) {
                if(node[idx].l && node[idx].r)
                    idx = node[idx].p;
                else
                    break;
            }
            if(idx == -1)
                break;
        }
        int ans[100] = {}, i;
        for(i = 0; i < size; i++) {
            if(node[i].v != -1) {
                ans[node[i].x-minx] += node[i].v;
            }
        }
        for(i = 0; i <= maxx-minx; i++) {
            if(i)
                printf(" ");
            printf("%d", ans[i]);
        }
        puts("\n");
    }
    return 0;
}
