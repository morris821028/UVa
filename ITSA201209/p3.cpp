#include <cstdio>

int main() {
    int t;
    scanf("%d", &t);
    while(t--) {
        int H, M, h, m, s, d;
        scanf("%d %d %d %d %d %d", &H, &M, &h, &m, &s, &d);
        H = H*60+M;
        h = h*60+m;
        H = h-H;
        if(H%60)    H = H/60+1;
        else    H = H/60;
        printf("%d\n", H*d*s);
    }
    return 0;
}
