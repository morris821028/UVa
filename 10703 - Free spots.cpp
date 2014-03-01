#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
int main() {
    int w, h, n;
    while(scanf("%d %d %d", &w, &h, &n) == 3) {
        if(w == 0)
            break;
        bool r[w+1][h+1];
        int i, j, ans = 0;
        int a, b, c, d;
        memset(r, 0, sizeof(r));
        while(n--) {
            scanf("%d %d %d %d", &a, &b, &c, &d);
            if(a > c)   swap(a, c);
            if(b > d)   swap(b, d);
            for(i = a; i <= c; i++)
                for(j = b; j <= d; j++)
                    r[i][j] = true;
        }
        for(i = 1; i <= w; i++)
            for(j = 1; j <= h; j++)
                ans += r[i][j] == false;
        if(ans == 0)
            puts("There is no empty spots.");
        else if(ans == 1)
            puts("There is one empty spot.");
        else
            printf("There are %d empty spots.\n", ans);
    }
    return 0;
}
