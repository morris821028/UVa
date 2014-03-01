#include <stdio.h>
#include <string.h>
#define maxL (1000000>>5)+1
#define GET(x) (mark[x>>5]>>(x&31)&1)
#define SET(x) (mark[x>>5] |= 1<<(x&31))
int mark[maxL];
int n, m;
void jump(int i, int idx) {
    if(idx < 1 || idx > n || GET(m))
        return;
    SET(idx);
    jump(i+1, idx+2*i+1);
    jump(i+1, idx-2*i-1);
}
int main() {
    while(scanf("%d %d", &n, &m) == 2) {
        if(!n && !m)    break;
        if(n > 48) {
            puts("Let me try!");
            continue;
        }
        memset(mark, 0, sizeof(mark));
        jump(1, 1);
        if(GET(m))
            puts("Let me try!");
        else
            puts("Don't make fun of me!");
    }
    return 0;
}
