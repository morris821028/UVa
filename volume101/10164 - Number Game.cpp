#include <stdio.h>
struct ND {
    int l, r, v;
};
ND BST[5000];
int size, i, flag;
void print(int nd) {
    if(BST[nd].l <0 && BST[nd].r <0) {
        if(flag)    putchar(' ');
        flag = 1;
        printf("%d", BST[nd].v);
        return;
    }
    print(BST[nd].l);
    print(BST[nd].r);
}
int main() {
    int n, m;
    int odd[5000], even[5000];
    while(scanf("%d", &n) == 1 && n) {
        m = 2*n-1;
        size = 1;
        while(size <= n)    size <<= 1;
        for(i = 0; i < m; i++) {
            scanf("%d", &BST[size+i].v);
            BST[size+i].l = -1, BST[size+i].r = -1;
        }

        int ot, et, pt;
        while(size > 1) {
            ot = 0, et = 0;
            for(i = 0; i < size-1; i++) {
                if(BST[size+i].v&1)
                    odd[ot++] = size+i;
                else
                    even[et++] = size+i;
            }
            pt = size>>1;
            if(ot&1)    ot--;
            if(et&1)    et--;
            for(i = 0; i < ot; i += 2) {
                BST[pt].v = (BST[odd[i]].v+BST[odd[i+1]].v)/2;
                BST[pt].l = odd[i];
                BST[pt].r = odd[i+1];
                pt++;
            }
            for(i = 0; i < et; i += 2) {
                BST[pt].v = (BST[even[i]].v+BST[even[i+1]].v)/2;
                BST[pt].l = even[i];
                BST[pt].r = even[i+1];
                pt++;
            }
            size >>= 1;
        }
        puts("Yes");
        flag = 0;
        print(2);
        puts("");
    }
    return 0;
}
