#include <stdio.h>
#include <set>
using namespace std;

int main() {
    int t, n, m, x, i;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &n, &m);
        set<int> ch[2];
        scanf("%d", &x);
        ch[0].insert(x%m);
        int flag;
        for(i = 1, flag = 0; i < n; i++, flag = 1-flag) {
            scanf("%d", &x);
            for(set<int>::iterator j = ch[flag].begin(); j != ch[flag].end(); j++) {
                ch[1-flag].insert((*j+x)%m);
                ch[1-flag].insert((*j-x)%m);
            }
            ch[flag].clear();
        }
        int ans = 0;
        for(set<int>::iterator j = ch[flag].begin(); j != ch[flag].end(); j++) {
            if(*j == 0)
                ans = 1;
        }
        puts(ans ? "Divisible" : "Not divisible");
    }
    return 0;
}
