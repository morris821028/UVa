#include <stdio.h>
char a[60], b[60];
int idx;
void find(int l, int r) {
    if(l > r)   return;
    int i;
    for(i = l; i <= r; i++) {
        if(b[i] == a[idx])
            break;
    }
    if(i != r+1) {
        idx++;
        find(l, i-1);
        find(i+1, r);
        putchar(b[i]);
    }
}
int main() {
    int t, n;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %s %s", &n, a, b);
        idx = 0;
        find(0, n-1);
        puts("");
    }
    return 0;
}
