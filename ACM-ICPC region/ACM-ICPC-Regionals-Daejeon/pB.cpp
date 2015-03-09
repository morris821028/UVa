#include <stdio.h>

int main() {
    int t, i, j;
    scanf("%d", &t);
    while(t--) {
        int a, b, c, ab, bc, ca;
        scanf("%d %d %d", &a, &b, &c);
        scanf("%d %d %d", &ab, &bc, &ca);
        int ans = 0;
        for(i = 0; ; i++) {
            if(i > a || i > b)  break;
            int ta = a-i, tb = b-i;
            for(j = 0; ; j++) {
                if(j > tb || j > c)    break;
                int tc = c-j;
                int mm = tc < ta ? tc : ta;
                int tmp = i*ab + j*bc + mm*ca;
                if(tmp > ans)
                    ans = tmp;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
