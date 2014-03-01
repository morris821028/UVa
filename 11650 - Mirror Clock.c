#include <stdio.h>

int main() {
    int t, h, w;
    scanf("%d", &t);
    while(t--) {
        scanf("%d:%d", &h, &w);
        h = 11-h + (w == 0);
        if(h <= 0)   h += 12;
        if(w != 0)
            w = 60-w;
        printf("%02d:%02d\n", h, w);
    }
    return 0;
}
