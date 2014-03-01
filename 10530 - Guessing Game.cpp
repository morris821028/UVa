#include <stdio.h>
#include <algorithm>
using namespace std;
int main() {
    int g, i;
    char cmd[10];
    while(1) {
        int l = 0, r = 11, flag = 0;
        for(i = 0; ; i++) {
            scanf("%d", &g);
            if(g == 0 && i == 0)
                break;
            scanf("%*s %s", cmd);
            if(cmd[0] == 'h') {
                r = min(g-1, r);
                if(l > r)   flag = 1;
            } else if(cmd[0] == 'l') {
                l = max(g+1, l);
                if(l > r)   flag = 1;
            } else {
                if(g < l || g > r)
                    flag = 1;
                break;
            }
        }
        if(i == 0 && g == 0)    break;
        if(flag)
            puts("Stan is dishonest");
        else
            puts("Stan may be honest");
    }
    return 0;
}
