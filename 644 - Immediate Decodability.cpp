#include <stdio.h>
typedef struct {
    int l, r, s;
} Node;
Node nd[10000];
int size, flag;
void Trie(char s[]) {
    static int i, idx;
    for(i = 0, idx = 0; s[i]; i++) {
        if(s[i] == '0') {
            if(!nd[idx].l)
                ++size, nd[idx].l = size,
                nd[size].l = 0, nd[size].r = 0, nd[size].s = 0;
            idx = nd[idx].l;
        }
        else {
            if(!nd[idx].r)
                ++size, nd[idx].r = size,
                nd[size].l = 0, nd[size].r = 0, nd[size].s = 0;
            idx = nd[idx].r;
        }
        if(nd[idx].s) {
            flag = 1;
            return;
        }
    }
    if(nd[idx].l || nd[idx].r)
        flag = 1;
    nd[idx].s = 1;
}
int main() {
    char s[100];
    int cases = 0;
    while(gets(s)) {
        flag = 0, size = 0;
        nd[0].l = 0, nd[0].r = 0;
        Trie(s);
        while(gets(s)) {
            if(s[0] == '9') break;
            if(flag)    continue;
            Trie(s);
        }
        printf("Set %d is %simmediately decodable\n", ++cases, !flag ? "" : "not ");
    }
    return 0;
}
