#include <stdio.h>

int main() {
    int t, cases = 0;
    scanf("%d", &t);
    while(t--) {
        int n, H, M;
        scanf("%d %d:%d", &n, &H, &M);
        int mn = 0xfffffff, h, m, c;
        H = H*60+M;
        while(n--) {
            scanf("%d:%d %d", &h, &m, &c);
            h = h*60+m;
            if(h < H)   h += 1440;
            h += c;
            if(mn > h)  mn = h;
        }
        printf("Case %d: %d\n", ++cases, mn-H);
    }
    return 0;
}
