#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
using namespace std;
struct {
    int x, y, a, b;
} cont[5];
char gcont[5][5] = {};
int m, contused[5] = {};
int check(int idx, int tx, int ty) {
    if(tx+cont[idx].a > 5 || ty+cont[idx].b > 5)
        return 0;
    int i, j;
    for(i = tx; i < tx+cont[idx].a; i++) {
        for(j = ty; j < ty+cont[idx].b; j++) {
            if(gcont[i][j])
                return 0;
        }
    }
    return 1;
}
int contx[5], conty[5];
int ans;
void dfs(int idx) {
    int tx, ty, i, j, k;
    if(idx == m) {
        for(i = 0; i <= 15; i++) {
            for(j = 0; j <= 15; j++) {
                int tmp = 0;
                for(k = 0; k < m; k++) {
                    tmp += abs(i+contx[k]-cont[k].x)+abs(j+conty[k]-cont[k].y);
                }
                if(tmp < ans)
                    ans = tmp;
            }
        }
        return;
    }
    for(i = 0; i < 5; i++) {
        for(j = 0; j < 5; j++) {
            if(gcont[i][j] == 0) {
                tx = i, ty = j;
                break;
            }
        }
        if(j != 5)  break;
    }
    for(i = 0; i < m; i++) {
        if(contused[i] == 0 && check(i, tx, ty)) {
            contused[i] = 1;
            for(j = tx; j < tx+cont[i].a; j++)
                for(k = ty; k < ty+cont[i].b; k++)
                    gcont[j][k] = i+1;
            contx[i] = tx, conty[i] = ty;
            dfs(idx+1);
            for(j = tx; j < tx+cont[i].a; j++)
                for(k = ty; k < ty+cont[i].b; k++)
                    gcont[j][k] = 0;
            contused[i] = 0;
        }
    }
}
int main() {
    int t;
    int cases = 0;
    scanf("%d", &t);
    while(t--) {
        char g[31][31];
        int i, j, hi, hj;
        m = 0;
        for(i = 0; i < 20; i++)
            scanf("%s", g[i]);
        int used[31][31] = {}, a, b;
        for(i = 0; i < 20; i++) {
            for(j = 0; j < 20; j++) {
                if(g[i][j] == 'x' && used[i][j] == 0) {
                    a = 0, b = 0;
                    while(g[i+a][j] == 'x')  a++;
                    while(g[i][j+b] == 'x')  b++;
                    for(hi = 0; hi < a; hi++)
                        for(hj = 0; hj < b; hj++)
                            used[i+hi][j+hj] = 1;
                    cont[m].x = i, cont[m].y = j;
                    cont[m].a = a, cont[m].b = b;
                    m++;
                }
            }
        }
        ans = 2147483647;
        dfs(0);
        printf("Case %d: ", ++cases);
        if(ans == 2147483647)
            cout << "invalid data" << endl;
        else {
            cout << ans << endl;
        }
    }
    return 0;
}
/*
2



....................

....................

....................

....................

....................

....................

..xxxxx.............

..xxxxx.............

....................

....................

..xx..........xxx...

....................

..xxxxx.............

..xxxxx.............

....................

....................

....................

....................

....................

....................



.................x..

....................

....................

....................

..xx................

..xx................

..xx................

..xx................

..xx................

..xx................

.......xxxxxx.......

.......xxxxxx.......

....................

....................

....................

....................

....................

....................

....................

....................
*/
